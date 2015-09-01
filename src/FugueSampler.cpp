#include "FugueSampler.h"

void FugueSampler::setup() {
	sampler.setup();

	sampler.newSample('a',1);
	sampler.openStream();

	sampler.record('a');
	usleep(2*1000000);

	sampler.play('a', 5);
	usleep(1*1000000);

	sampler.closeStream();

	exit(0);

}

void FugueSampler::update(unsigned long long tick) {
}

//----------------------------------------------------------------
int FugueSampler::getUniqueEventCount() {
	if(!file.status()) {
		cerr << "Error reading MIDI file" << endl;
	}

	file.doTimeAnalysis();
	file.linkNotePairs();

	return 0;
}
