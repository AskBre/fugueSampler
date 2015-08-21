#include "RtAudio.h"
#include <iostream>

#define SAMPLE_RATE 48000
#define BUFFER_FRAMES 256


using namespace std;

enum state_t {STOP, REC, PLAY};

struct audioData_t {
	state_t state;
	int32_t *buffer;
	unsigned bufferSize;
	unsigned iteration = 0;
};

int recAndPlay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData);

int main() {
	RtAudio adc;
	if (adc.getDeviceCount() < 1 ) {
		cout << "\nNo audio devices found!" << endl;
		exit(0);
	}

	unsigned sampleRate = SAMPLE_RATE;
	unsigned bufferFrames = BUFFER_FRAMES;

	RtAudio::StreamParameters iParams, oParams;
	iParams.deviceId = adc.getDefaultInputDevice();
	iParams.nChannels = 2;
	oParams.deviceId = adc.getDefaultOutputDevice();
	oParams.nChannels = 2;

	audioData_t audioData;
	audioData.state = STOP;
	audioData.bufferSize = 48000*sizeof(int32_t);

	if(!(audioData.buffer = (int32_t *) malloc (audioData.bufferSize))) { // Try to allocate 1 second of audio
		cout << "Failed to allocate memory" << endl;
		exit(0);
	}

	try {
		adc.openStream( &oParams, &iParams, RTAUDIO_SINT32, sampleRate, &bufferFrames, &recAndPlay, &audioData);
		adc.startStream();
	} catch (RtAudioError &error) {
		error.printMessage();
		exit(0);
	}

	while(1) {
		char input;
		cin.get( input );
		switch(input) {
			case 'r':
				audioData.state = REC;
				break;
			case 'p':
				audioData.state = PLAY;
				break;
			case 's':
				audioData.state = STOP;
				break;
			default:
				break;
		}
	}

	try {
		adc.stopStream();
	} catch(RtAudioError& e) {
		e.printMessage();
	}

	if(adc.isStreamOpen()) adc.closeStream();

	return 0;
}

int recAndPlay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData) {

	audioData_t *data = static_cast<audioData_t*>(userData);
	int32_t *inBuffer = static_cast<int32_t*> (inputBuffer);
	int32_t *outBuffer = static_cast<int32_t*> (outputBuffer);

	if (status) cout << "Stream overflow detected!" << endl;

	if(data->state == REC) {

		if(data->iteration < SAMPLE_RATE/nBufferFrames) {
			for(unsigned i=0; i<nBufferFrames; i++) {
				unsigned j = i + (nBufferFrames * data->iteration);

				if(j < data->bufferSize) {
					data->buffer[j] = inBuffer[i];
				} else {
					return 0;
				}
			}

			data->iteration++;
		} else {
			data->state = STOP;
			data->iteration = 0;
		}

	} else if (data->state == PLAY) {

		if(data->iteration < SAMPLE_RATE/nBufferFrames) {
			for(unsigned i=0; i<nBufferFrames; i++) {
				unsigned j = i + (nBufferFrames * data->iteration);

				if(j < data->bufferSize) {
					outBuffer[i] = data->buffer[j];
				} else {
					return 0;
				}
			}

			data->iteration++;
		} else {
			data->state = STOP;
			data->iteration = 0;
		}

	} else if (data->state == STOP) {
		return 0;
	} else {
		cout << "Couldn't get state from audioData" << endl;
		exit(0);
	}

	return 0;
}
