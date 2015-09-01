#include "SamplerSample.h"

void SamplerSample::record(double *inBuffer) {
	cout << "Recording sample " <<  name << endl;
	if( iteration < sampleRate/bufferFrames) {
		for(unsigned i=0; i<bufferFrames; i++) {
			unsigned j = i + (bufferFrames *  iteration);
			if(j <  bufferSize) {
				buffer[j] = inBuffer[i];
			} else {
				break;
			}
		}

		iteration++;
	} else {
		state = STOP;
		iteration = 0;
		memset(inBuffer, 0, bufferFrames);
	}
}

void SamplerSample::play(double *outBuffer) {
	cout << "Playing sample " <<  name << endl;
	//						<-- Need to setup sample length too!
	if( iteration < sampleRate/bufferFrames) {
		for(unsigned i=0; i<bufferFrames; i++) {
			unsigned j = i + (bufferFrames *  iteration);

			if(j <  bufferSize) {
				outBuffer[i] =  buffer[j];
			} else {
				break;
			}
		}

		iteration++;
	} else {
		memset(outBuffer, 0, bufferFrames);
		state = STOP;
		iteration = 0;
	}

}
