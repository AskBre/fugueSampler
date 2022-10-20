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

enum runState_t { IDLE, RUN, REACHED_END, STOPPED };

class FugueSampler {
	public:
		void setup(string fileName, bool _shouldLoop);
		void update();
		void ampDetect();

		bool shouldLoop;
		Sampler sampler;
		runState_t runState = IDLE;

	private:
		void recAndPlay(unsigned long long tick);
		void allocateSamples();

		smf::MidiFile file;

		unsigned long tick = 0;
		unsigned nTracks;
		unsigned nEvents = 0;
		unsigned eventCounter = 0;
		unsigned oldPercent = 100;

		vector<unsigned> indices;
};
