#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	if(iteration < bufferSize) {
		for(unsigned i=0; i<bufferFrames; i++) {
			unsigned j = i + iteration;
			if(j < bufferSize) {
				buffer[j] = inBuffer[i];
			} else {
				break;
			}
		}

		iteration += bufferFrames;
	} else {
		state = STOP;
		iteration = 0;
		memset(inBuffer, 0, bufferFrames);
		isRecorded = true;
	}

}

void SamplerSample::play(double *outBuffer) {
	if(iteration < sampleLengthInFrames) {
		for(unsigned i=0; i<bufferFrames; i+=2) {
			unsigned j = (i/2) + iteration;
			if(j < bufferSize) {
				outBuffer[i] = buffer[j];
				outBuffer[i+1] = buffer[j];
			} else {
			}
		}

		iteration += bufferFrames;
	} else {
		state = STOP;
		iteration = 0;
		memset(outBuffer, 0, bufferFrames);
	}
}
