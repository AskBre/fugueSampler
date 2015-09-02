#pragma once

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include <signal.h>

#include "MidiFile.h"

#include "Sampler.h"

using namespace std;

class FugueSampler {
	public:
		void setup(string fileName);
		void update(unsigned long long tick);
		Sampler sampler;
		bool isDone = false;

	private:
		MidiFile file;
		void allocateSamples();

		unsigned index = 0;

		unsigned trackCount;
		unsigned eventCount;
		vector<unsigned> indices;
};
