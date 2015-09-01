#include "FugueSampler.h"

void FugueSampler::setup() {
	sampler.setup();

	sampler.newTrack('a',2);

	sampler.openStream();
}

void FugueSampler::update(unsigned long long tick) {
	sampler.play('a', 0.25);
	sampler.closeStream();
}

//----------------------------------------------------------------
void FugueSampler::getUniqueEventCount() {
	if(!file.status()) {
		cerr << "Error reading MIDI file" << endl;
	}

	file.doTimeAnalysis();
	file.linkNotePairs();
}

void recordSound(
