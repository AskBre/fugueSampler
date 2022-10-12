#pragma once

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>

#include "MidiFile.h"

#include "Sampler.h"

#define THRES 0.05

using namespace std;

enum runState_t { IDLE, RUN, STOPPED };

class FugueSampler {
	public:
		void setup(string fileName);
		void update(unsigned long long tick);
		void ampDetect();
		Sampler sampler;
		runState_t runState = IDLE;

	private:
		smf::MidiFile file;
		void allocateSamples();

		unsigned index = 0;

		unsigned nTracks;
		unsigned nEvents = 0;
		unsigned eventCounter;
		unsigned oldPercent = 100;
		vector<unsigned> indices;
};
