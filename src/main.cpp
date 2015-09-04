#include <unistd.h>

#include "FugueSampler.h"

using namespace std;


int main() {
	FugueSampler fugueSampler;

	fugueSampler.setup("ricercar_6_full.mid");

	while(fugueSampler.runState == IDLE) {
		usleep(100000);
		fugueSampler.ampDetect();
	}

	// Miditick
	unsigned long long tick = 0;
	while(fugueSampler.runState==RUN) {
		fugueSampler.update(tick);
		usleep(1000);
		tick++;
	}

	fugueSampler.sampler.closeStream();
	cout << "Well played!" << endl;

	return 0;
}
