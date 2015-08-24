#include "MidiFile.h"
#include "Options.h"
#include <iostream>

#include "Sampler.h"

using namespace std;

int main() {
	Sampler sampler;

	sampler.setup();
	sampler.newTrack('a',1);
	sampler.newTrack('b',1);
	sampler.openStream();

	while(1) {
		char input;
		cin.get( input );
		switch(input) {
			case 'r':
				sampler.record('a');
				sampler.record('b');
				break;
			case 'p':
//				audioData.state = PLAY;
				break;
			case 's':
//				audioData.state = STOP;
				break;
			default:
				break;
		}
	}
	
	sampler.closeStream();

	return 0;
}


