#include "FugueSampler.h"

void FugueSampler::setup(string fileName, bool _shouldLoop) {
	shouldLoop = _shouldLoop;

	file.read(fileName);
	if(!file.status()) {
		cerr << "Error reading MIDI file " << fileName << endl;
		exit(2);
	}

	file.doTimeAnalysis();
	file.linkNotePairs();

	nTracks = file.getTrackCount();
	indices.resize(nTracks);

	sampler.setup();

	allocateSamples();

	sampler.openStream();
}

void FugueSampler::update() {
	if(runState == RUN) {
		recAndPlay(tick);
		usleep(1000);
		tick++;
	} else if(runState == REACHED_END) {
		tick = 0;
		runState = RUN;
	} else if (runState == STOPPED) {
		exit(0);
	}

}

void FugueSampler::ampDetect() {
	double amp = sampler.getAmplitude();
	cout << amp << endl;
	if(amp > THRES) {
		runState = RUN;
	}

	// If debugging without audio input, don't wait for audio input 
	runState = RUN;
}

//----------------------------------------------------------------
void FugueSampler::recAndPlay(unsigned long long tick) {
	for(unsigned track=0; track < nTracks; track++) {
		unsigned index = indices.at(track);
		if(file.getEventCount(track) > index) {
			if(file[track][index].isNoteOn()) {

				smf::MidiEvent event = file.getEvent(track, index);
				float duration = file[track][index].getDurationInSeconds();

				if(event.tick < tick) {
					const char name = event.at(1);

					if(sampler.isRecorded(name)) {
						cout << "Playing " << name << endl;
						sampler.play(name, duration);
					} else {
						sampler.record(name);
						cout << "Recording " << name << endl;
					}

					indices.at(track)++;
					eventCounter++;

					unsigned percent =
						(float)eventCounter/(float)nEvents*100;
					if(percent!=oldPercent) {
						cout << percent << "%" << endl;
					}

					oldPercent = percent;
				}
			} else {
				indices.at(track)++;
			}
		} else if (shouldLoop && index > nEvents) {
			cout << "LOooooooOOOOOOoooooooooooooooOOooooooooooooooooOOooooooOOooOOOOOOooooooooooooooping!" << endl;
			runState = REACHED_END;
			eventCounter = 0;
			indices.at(track) = 0;
		}
	}
}

void FugueSampler::allocateSamples() {
	vector< vector<unsigned char> > cache;

	for(unsigned t=0; t<file.getTrackCount(); t++) {
		for(unsigned e=0; e<file.getEventCount(t); e++) {
			if(file[t][e].isNoteOn()) {
				nEvents++;

				vector<unsigned char> event;
				for(auto m : file[t][e]) {
					event.push_back(m);
				}

				bool isPresent = find(cache.begin(), cache.end(), event) != cache.end();

				if(!isPresent) {
					cache.push_back(event);

					float duration = file[t][e].getDurationInSeconds();
					char name = file[t][e][1];

					sampler.newSample(name, duration);
				}
			}
		}
	}

	cout << "Filled " << cache.size() << " samples" << endl;
}
