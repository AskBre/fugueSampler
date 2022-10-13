#include <unistd.h>

#include "FugueSampler.h"

using namespace std;


int main(int argc, char *argv[] ) {
	FugueSampler fugueSampler;
	bool shouldLoop = true;

	if(argc){
		fugueSampler.setup(argv[1], shouldLoop);
	} else {
		cout << "Need input midi file" << endl;
		exit(1);
	}

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

		if(fugueSampler.runState == REACHED_END) tick = 0;
	}

	fugueSampler.sampler.closeStream();
	cout << "Well played!" << endl;

	return 0;
}
