#include <unistd.h>

#include "FugueSampler.h"

using namespace std;

int main() {
	FugueSampler fugueSampler;
	fugueSampler.setup("ricercar_6_full.mid");

	// Miditick
	unsigned long long tick = 0;
	while(!fugueSampler.isDone) {
		fugueSampler.update(tick);
		usleep(1000);
		tick++;
	}

	cout << "Well played!" << endl;

	return 0;
}
