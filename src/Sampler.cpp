#include "Sampler.h"

void Sampler::setup() {
	if (audio.getDeviceCount() < 1 ) {
		cerr << "No audio devices found!" << endl;
		exit(0);
	}
	cout << "Available devices is " << endl;
	for(unsigned i = 0; i<audio.getDeviceCount(); i++) {

		RtAudio::DeviceInfo info = audio.getDeviceInfo(i);
		cout << info.name << endl;
	}
	cout << endl;

	iParams.deviceId = audio.getDefaultInputDevice();
	iParams.nChannels = 2;

	oParams.deviceId = audio.getDefaultOutputDevice();
	oParams.nChannels = 2;

	if(!(audioData.inBuffer = (double *) malloc (BUFFER_FRAMES * sizeof(double)))) {
	}
}

void Sampler::openStream() {
	unsigned int nBufferFrames = BUFFER_FRAMES;
	unsigned int sampleRate = SAMPLE_RATE;
	try {
		audio.openStream( &oParams, &iParams, RTAUDIO_FLOAT64, sampleRate,
				&nBufferFrames, &recAndPlay, static_cast<void*>(&audioData));
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

//----------------------------------------------------------------
void Sampler::newSample(const char sampleName, const float sampleLengthInSec) {
	if(getSampleIndex(sampleName) != -1) {
		cerr << "Samplename " << (unsigned)sampleName << " already exists!" << endl;
		return;
	}

	SamplerSample sample;

	sample.name = sampleName;
	sample.bufferSize = SAMPLE_RATE*4;
	sample.sampleRate = SAMPLE_RATE;
	sample.bufferFrames = BUFFER_FRAMES;

	if(!(sample.buffer = (double *) malloc (sample.bufferSize * sizeof(double)))) {
		cerr << "Failed to allocate memory" << endl;
		exit(0);
	}

	audioData.samples.push_back(sample);
	cout << "Added new sample " << (unsigned) sample.name << " of length " << sampleLengthInSec << endl;
}

//----------------------------------------------------------------
void Sampler::record(const char sampleName) {
	int i = getSampleIndex(sampleName);

	if (i == -1) {
		cerr << "No sample found with name " << sampleName << endl;
		exit(0);
	} else {
		audioData.samples[i].state = REC;
	}
}

void Sampler::play(const char sampleName, const float sampleLengthInSec) {
	int i = getSampleIndex(sampleName);

	if (i == -1) {
		cerr << "No sample found with name " << sampleName << endl;
		exit(0);
	} else if (audioData.samples[i].state == REC) {
		cerr << "Can't play sample " << sampleName << " while recording" << endl;
	} else {
		float sampleLengthInFrames = sampleLengthInSec * SAMPLE_RATE;
		audioData.samples[i].sampleLengthInFrames = sampleLengthInFrames;
		audioData.samples[i].state = PLAY;
	}
}

//----------------------------------------------------------------
bool Sampler::isRecorded(const char &name) {
	return audioData.samples.at(getSampleIndex(name)).isRecorded;
}

double Sampler::getAmplitude() {

	double amp = 0;
	for(int i=0; i<BUFFER_FRAMES; i++) {
		if(audioData.inBuffer[i] > amp) amp = audioData.inBuffer[i];
	}

	return amp;
}

// Private
//----------------------------------------------------------------
int Sampler::getSampleIndex(const char &name) {
	for(int i=0; i<audioData.samples.size(); i++) {
		if (audioData.samples[i].name == name) return i;
	}

	return -1;
}

// Outside (But want to move in?)
//----------------------------------------------------------------
int recAndPlay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData) {

	audioData_t *audioData = static_cast<audioData_t*> (userData);
	vector<SamplerSample> *samples = &audioData->samples;

	double *inBuffer = static_cast<double*> (inputBuffer);
	double *outBuffer = static_cast<double*> (outputBuffer);
	audioData->inBuffer = inBuffer;

	memset(outputBuffer, 0, nBufferFrames * 2 * sizeof(double));

	if (status) cerr << "Stream overflow detected!" << endl;

	for(auto &sample : *samples) {
		if(sample.state == REC) {
			sample.record(inBuffer);
		} else if (sample.state == PLAY) {
			sample.play(outBuffer);
		} else if (sample.state == STOP) {
		} else {
			cerr << "Couldn't get state from sample" << endl;
			exit(0);
		}
	}
	return 0;
}
