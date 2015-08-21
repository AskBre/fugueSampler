#include "RtAudio.h"
#include <iostream>

using namespace std;

int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData);

int main() {
	RtAudio adc;
	if (adc.getDeviceCount() < 1 ) {
		cout << "\nNo audio devices found!" << endl;
		exit(0);
	}

	RtAudio::StreamParameters parameters;
	parameters.nChannels = 2;
	parameters.deviceId = adc.getDefaultInputDevice();
	parameters.firstChannel = 0;
	unsigned int sampleRate = 48000;
	unsigned int bufferFrames = 256;
	string myData = "This is my data!";

	try {
		adc.openStream( NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, &record, &myData);
		adc.startStream();
	} catch (RtAudioError &error) {
		error.printMessage();
		exit(0);
	}

	char input;
	cout << "Recording ... press <enter> to quit." << endl;
	cin.get( input );

	cout << "The data is now: " << myData << endl;

	try {
		adc.stopStream();
	} catch(RtAudioError& e) {
		e.printMessage();
	}

	if(adc.isStreamOpen()) adc.closeStream();

	return 0;
}

int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData) {

	string *lDataP = static_cast<string*>(userData);

	if (status) cout << "Stream overflow detected!" << endl;

	// Do stuff with input
	
	*lDataP = "This is my modified data!!! (Oh, and it works)";

	return 0;
}


