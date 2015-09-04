#include <unistd.h>

#include "FugueSampler.h"

using namespace std;

enum runState_t {
	IDLE;
	RUN;
	STOPPED;
}

int main() {
	FugueSampler fugueSampler;
	fugueSampler.setup("ricercar_6_full.mid");

	// Miditick
	unsigned long long tick = 0;
	while(fugueSampler.runState != STOPPED) {
		if(fugueSampler.runState == IDLE) {
			fugueSampler.ampDetect();
		} else if (fugueSampler.runState==RUN) {
			fugueSampler.update(tick);
			usleep(1000);
			tick++;
		}
	}

	fugueSampler.sampler.closeStream();
	cout << "Well played!" << endl;

	return 0;
}
