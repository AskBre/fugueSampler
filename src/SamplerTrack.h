#include <iostream>
#include <string.h>

enum state_t {STOP, REC, PLAY};

using namespace std;

class SamplerTrack {
	public:
		char name;
		state_t state = STOP;
		float trackLengthInSec;
		unsigned iteration = 0;

		double *buffer;
		unsigned bufferSize;
		unsigned sampleRate;
		unsigned bufferFrames;

		void record(double *inBuffer);
		void play(double *outBuffer);
		void stop();
};
