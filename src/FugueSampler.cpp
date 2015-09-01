#include "FugueSampler.h"

void FugueSampler::setup() {
	sampler.setup();

	/*
	sampler.newSample('a',1);
	sampler.openStream();
	sampler.record('a');
	sampler.play('a', 5);
	sampler.closeStream();
	*/

	exit(0);

}

void FugueSampler::update(unsigned long long tick) {
}

void FugueSampler::setMidiFile(string newFile) {
	file.read(newFile);
	file.doTimeAnalysis();
	file.linkNotePairs();
}

//----------------------------------------------------------------
int FugueSampler::getUniqueEventCount() {
	if(!file.status()) {
		cerr << "Error reading MIDI file" << endl;
	}

	return 0;
}
