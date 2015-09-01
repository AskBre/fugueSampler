#pragma once
#include <iostream>
#include <string.h>

#include "Sampler.h"

enum state_t {STOP, REC, PLAY};

using namespace std;

class SamplerSample : public Sampler {
	public:
		char name;
		state_t state = STOP;
		float sampleLengthInSec;
		unsigned iteration = 0;

		double *buffer;
		unsigned bufferSize;
		unsigned sampleRate;
		unsigned bufferFrames;

		void record(double *inBuffer);
		void play(double *outBuffer);
		void stop();
};
