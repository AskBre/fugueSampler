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

	while(true) {
		fugueSampler.update();
	}

	fugueSampler.sampler.closeStream();
	cout << "Well played!" << endl;

	return 0;
}
