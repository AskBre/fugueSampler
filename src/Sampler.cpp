#include "Sampler.h"

void Sampler::setup() {
	if (audio.getDeviceCount() < 1 ) {
		cout << "No audio devices found!" << endl;
		exit(0);
	}

	cout << "Available devices is " << endl;
	for(unsigned i = 0; i<audio.getDeviceCount(); i++) {
		RtAudio::DeviceInfo info = audio.getDeviceInfo(i);
		cout << info.name << endl;
	}

	// Should I add user-picking of devices?
	iParams.deviceId = audio.getDefaultInputDevice();
	iParams.nChannels = 2;

	oParams.deviceId = audio.getDefaultOutputDevice();
	oParams.nChannels = 2;
}

void Sampler::newSample(const char sampleName, const float sampleLengthInSec) {
	if(getSampleIndex(sampleName) != -1) {
		cerr << "Samplename " << sampleName << " already exists!" << endl;
		exit(0);
	}

	SamplerSample sample;

	sample.name = sampleName;
	sample.bufferSize = SAMPLE_RATE*sampleLengthInSec;
	sample.sampleRate = SAMPLE_RATE;
	sample.bufferFrames = BUFFER_FRAMES;

	if(!(sample.buffer = (double *) malloc (sample.bufferSize * sizeof(double)))) {
		cerr << "Failed to allocate memory" << endl;
		exit(0);
	}
	cout << "Buffersize is " << sample.bufferSize << endl;
	cout << "Size of buffer is " << sizeof(sample.buffer[0]) << endl;

	samples.push_back(sample);
	cout << "Added new sample " << sample.name << " of length " << sampleLengthInSec << endl;
}

void Sampler::openStream() {
	unsigned int nBufferFrames = BUFFER_FRAMES;
	unsigned int sampleRate = SAMPLE_RATE;
	try {
		audio.openStream( &oParams, &iParams, RTAUDIO_FLOAT32, sampleRate,
				&nBufferFrames, &recAndPlay, &samples);
		audio.startStream();
	} catch (RtAudioError &error) {
		error.printMessage();
		exit(0);
	}
	cout << "Audio stream opened" << endl;
}

void Sampler::closeStream() {
	try {
		audio.stopStream();
	} catch(RtAudioError& e) {
		e.printMessage();
	}

	if(audio.isStreamOpen()) audio.closeStream();

	cout << "Audio stream closed" << endl;
}

void Sampler::record(const char sampleName) {
	int i = getSampleIndex(sampleName);
	//						<-- Need to setup sample length too!

	if (i == -1) {
		cerr << "No sample found with name " << sampleName << endl;
		exit(0);
	} else {
		samples[i].state = REC;
	}
}

void Sampler::play(const char sampleName, const float sampleLengthInSec) {
	int i = getSampleIndex(sampleName);

	if (i == -1) {
		cerr << "No sample found with name " << sampleName << endl;
		exit(0);
	} else if (samples[i].state == REC) {
		cout << "Can't play sample " << sampleName << " while recording" << endl;
	} else {
		float sampleLengthInFrames = sampleLengthInSec * SAMPLE_RATE;
		samples[i].sampleLengthInFrames = sampleLengthInFrames;
		samples[i].state = PLAY;
	}
}

// Private
//----------------------------------------------------------------

int Sampler::getSampleIndex(const char &name) {
	for(int i=0; i<samples.size(); i++) {
		if (samples[i].name == name) return i;
	}

	return -1;
}

// Outside (But want to move in?)
//----------------------------------------------------------------
int recAndPlay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData) {

	// Should I do the casting in SamplerSample?
	vector<SamplerSample> *samples = static_cast<vector <SamplerSample> *> (userData);
	double *inBuffer = static_cast<double*> (inputBuffer);
	double *outBuffer = static_cast<double*> (outputBuffer);

	if (status) cout << "Stream overflow detected!" << endl;

	for(auto &sample : *samples) {
		if(sample.state == REC) {
			sample.record(inBuffer);
		} else if (sample.state == PLAY) {
			sample.play(outBuffer);
		} else if (sample.state == STOP) {
			return 0;
		} else {
			cout << "Couldn't get state from sample" << endl;
			exit(0);
		}
	}
	return 0;
}
