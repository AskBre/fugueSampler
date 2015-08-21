#include "RtAudio.h"
#include <iostream>

#define SAMPLE_RATE 48000
#define BUFFER_FRAMES 256


using namespace std;

enum state_t {STOP, REC, PLAY};

struct audioData_t {
	state_t state;
	int *buffer;
};

int recAndPlay( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData);

int main() {
	RtAudio adc;
	if (adc.getDeviceCount() < 1 ) {
		cout << "\nNo audio devices found!" << endl;
		exit(0);
	}

	RtAudio::StreamParameters iParams, oParams;
	iParams.deviceId = adc.getDefaultInputDevice();
	iParams.nChannels = 1;
	oParams.deviceId = adc.getDefaultOutputDevice();
	oParams.nChannels = 1;

	audioData_t audioData;
	audioData.state = STOP;
	if(!(audioData.buffer = malloc (SAMPLE_RATE * sizeof (int)))) { // Try to allocate 1 second of audio
		cout << "Failed to allocate memory" << endl;
		exit(0);
	}

	try {
		adc.openStream( &oParams, &iParams, RTAUDIO_SINT24, SAMPLE_RATE, BUFFER_FRAMES, &recAndPlay, &audioData);
		adc.startStream();
	} catch (RtAudioError &error) {
		error.printMessage();
		exit(0);
	}

	char input;
	cout << "Running, press enter to exit." << endl;
	cin.get( input );

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

	audioData_t *lDataP = static_cast<audioData*>(userData);

	if (status) cout << "Stream overflow detected!" << endl;

	if(state == REC) {
	} else if (state == PLAY) {
	} else if (state == STOP) {
		return 0;
	} else {
		cout << "Couldn't get state from audioData" << endl;
		exit(0);
	}


	return 0;
}
