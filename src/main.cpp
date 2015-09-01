#include "FugueSampler.h"

using namespace std;

void main() {
	FugueSampler fugueSampler;
	fugueSampler setup();

	// Setup miditick
	unsigned long long tick = 0;
	while(1) {
		fugueSampler.update(tick);
		sleep(1000);
		tick++;
	}
	
	sampler.closeStream();
}
