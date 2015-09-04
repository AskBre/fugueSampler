#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	if(iteration < bufferSize-bufferFrames) {
		for(unsigned i=0; i<bufferFrames; i++) {
			unsigned j = iteration + i;
			buffer[j] = inBuffer[i];
		}
		iteration += bufferFrames;
	} else {
		state = STOP;
		iteration = 0;
		isRecorded = true;
	}

}

void SamplerSample::play(double *outBuffer) {
	if(iteration < bufferSize-bufferFrames) {
		for(unsigned i=0; i<bufferFrames*2; i+=2) {
			unsigned j = iteration + (i/2);
			outBuffer[i] += buffer[j];
			outBuffer[i+1] += buffer[j];
		}
		iteration += bufferFrames;
	} else {
		state = STOP;
		iteration = 0;
	}
}
