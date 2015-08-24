#include "SamplerTrack.h"

void SamplerTrack::record(double *inBuffer) {
	cout << "Recording track " <<  name << endl;
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

void SamplerTrack::play(double *outBuffer) {
	cout << "Playing track " <<  name << endl;

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
		state = STOP;
		iteration = 0;
		memset(outBuffer, 0, bufferFrames);
	}

}
