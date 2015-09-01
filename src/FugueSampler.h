#pragma once

#include <iostream>
#include <algorithm>
#include "Sampler.h"
#include "MidiFile.h"

class FugueSampler {
	public:
		void setup();
		void update(unsigned long long tick);
	private:
		MidiFile file;
		Sampler sampler;
		int getUniqueEventCount();
}
