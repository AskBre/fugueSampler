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

int Sampler::newTrack(const char name, const float seconds) {
	track_t track;

	auto pred = [name](const track_t & track) {
		return track.name == name;
	};

	if(find_if(begin(tracks), end(tracks), pred) != end(tracks)) {
		cerr << "This trackname already exists!" << endl;
		exit(0);
	}

	track.name = name;
	track.bufferSize = (SAMPLE_RATE*seconds) * sizeof(double);

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
	tracks[0].state = REC;
	tracks[1].state = REC;
	return 0;
}

int Sampler::play(const char trackName, const float seconds) {
	return 0;
}

// Private
//----------------------------------------------------------------

int recAndPlay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData) {

	// Need to double check the pointer arithmetics going on here,
	// doesn't seem to be pointing at all — just creating new tracks!
	vector<track_t> *tracks = static_cast<vector <track_t> *> (userData);
	double *inBuffer = static_cast<double*> (inputBuffer);
	double *outBuffer = static_cast<double*> (outputBuffer);

	if (status) cout << "Stream overflow detected!" << endl;

	for(auto &track : *tracks) {
		if(track.state == REC) {
			if(track.iteration < SAMPLE_RATE/nBufferFrames) {
				for(unsigned i=0; i<nBufferFrames; i++) {
					unsigned j = i + (nBufferFrames * track.iteration);
					if(j < track.bufferSize) {
						track.buffer[j] = inBuffer[i];
					} else {
						return 0;
					}
				}

				track.iteration++;
			} else {
				track.state = STOP;
				track.iteration = 0;
				memset(inBuffer, 0, nBufferFrames);
			}
		} else if (track.state == PLAY) {

			if(track.iteration < SAMPLE_RATE/nBufferFrames) {
				for(unsigned i=0; i<nBufferFrames; i++) {
					unsigned j = i + (nBufferFrames * track.iteration);

					if(j < track.bufferSize) {
						outBuffer[i] = track.buffer[j];
					} else {
						return 0;
					}
				}

				track.iteration++;
			} else {
				track.state = STOP;
				track.iteration = 0;
				memset(outBuffer, 0, nBufferFrames);
			}

		} else if (track.state == STOP) {
			return 0;
		} else {
			cout << "Couldn't get state from track" << endl;
			exit(0);
		}
	}

	return 0;
}
