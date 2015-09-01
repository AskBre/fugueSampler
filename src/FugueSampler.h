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
		void setup();
		void update(unsigned long long tick);
		void setMidiFile(string newFile);
		Sampler sampler;
	private:
		MidiFile file;
		int getUniqueEventCount();
};
