#include "MidiFile.h"
#include "Options.h"
#include <iostream>

#include "Sampler.h"

using namespace std;

int main() {
	Sampler sampler;

	sampler.setup();
	sampler.newTrack('a',2);
	sampler.openStream();

	while(1) {
		char input;
		cin.get( input );
		switch(input) {
			case 'r':
				sampler.record('a');
				break;
			case 'p':
				sampler.play('a', 0.25);
//				audioData.state = PLAY;
				break;
			case 's':
//				audioData.state = STOP;
				break;
			case 'q':
				sampler.closeStream();
				exit(0);
				break;
			default:
				break;
		}
	}
	
	sampler.closeStream();

	return 0;
}
