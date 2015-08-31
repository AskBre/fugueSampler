#include "Sampler.h"

int Sampler::setup() {

	if (audio.getDeviceCount() < 1 ) {
		cout << "No audio devices found!" << endl;
		exit(0);
	}

	iParams.deviceId = audio.getDefaultInputDevice();
	iParams.nChannels = 2;

	oParams.deviceId = audio.getDefaultOutputDevice();
	oParams.nChannels = 2;

	return 0;
}

int Sampler::newTrack(const char trackName, const float trackLengthInSec) {
	if(getTrackIndex(trackName) != -1) {
		cerr << "Trackname " << trackName << " already exists!" << endl;
		exit(0);
	}

	SamplerTrack track;

	track.name = trackName;
	track.bufferSize = (SAMPLE_RATE*trackLengthInSec) * sizeof(double);
	track.sampleRate = SAMPLE_RATE;
	track.bufferFrames = BUFFER_FRAMES;

	if(!(track.buffer = (double *) malloc (track.bufferSize))) {
		cout << "Failed to allocate memory" << endl;
		exit(0);
	}

	tracks.push_back(track);
	cout << "Added new track " << track.name << endl;
	return 0;
}

int Sampler::openStream() {

	unsigned int nBufferFrames = BUFFER_FRAMES;
	unsigned int sampleRate = SAMPLE_RATE;
	try {
		audio.openStream( &oParams, &iParams, RTAUDIO_FLOAT32, sampleRate,
				&nBufferFrames, &recAndPlay, &tracks);
		audio.startStream();
	} catch (RtAudioError &error) {
		error.printMessage();
		exit(0);
	}
	cout << "Audio stream opened" << endl;

	return 0;
}

int Sampler::closeStream() {
	try {
		audio.stopStream();
	} catch(RtAudioError& e) {
		e.printMessage();
	}

	if(audio.isStreamOpen()) audio.closeStream();

	cout << "Audio stream closed" << endl;

	return 0;
}

int Sampler::record(const char trackName) {
	int i = getTrackIndex(trackName);

	if (i == -1) {
		cerr << "No track found with name " << trackName << endl;
		exit(0);
	} else {
		tracks[i].state = REC;
	}

	return 0;
}

int Sampler::play(const char trackName, const float trackLengthInSec) {
	int i = getTrackIndex(trackName);

	if (i == -1) {
		cerr << "No track found with name " << trackName << endl;
		exit(0);
	} else {
		tracks[i].trackLengthInSec = trackLengthInSec;
		tracks[i].state = PLAY;
	}

	return 0;
}

// Private
//----------------------------------------------------------------

int Sampler::getTrackIndex(const char &name) {
	for(int i=0; i<tracks.size(); i++) {
		if (tracks[i].name == name) return i;
	}

	return -1;
}

// Outside (But want to move in?)
//----------------------------------------------------------------
int recAndPlay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData) {

	// Should I do the casting in SamplerTrack?
	vector<SamplerTrack> *tracks = static_cast<vector <SamplerTrack> *> (userData);
	double *inBuffer = static_cast<double*> (inputBuffer);
	double *outBuffer = static_cast<double*> (outputBuffer);

	if (status) cout << "Stream overflow detected!" << endl;

	for(auto &track : *tracks) {
		if(track.state == REC) {
			track.record(inBuffer);
		} else if (track.state == PLAY) {
			track.play(outBuffer);
		} else if (track.state == STOP) {
			return 0;
		} else {
			cout << "Couldn't get state from track" << endl;
			exit(0);
		}
	}
	return 0;
}
