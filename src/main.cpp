#include <unistd.h>

#include "FugueSampler.h"

using namespace std;

int main() {
	FugueSampler fugueSampler;
	fugueSampler.setup();

	// Setup miditick
	unsigned long long tick = 0;
	while(1) {
		fugueSampler.update(tick);
		usleep(1000);
		tick++;
	}

	return 0;
}
