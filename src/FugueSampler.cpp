#include "FugueSampler.h"

void FugueSampler::setup(string fileName) {
	file.read(fileName);
	if(!file.status()) {
		cerr << "Error reading MIDI file" << endl;
	}

	file.doTimeAnalysis();
	file.linkNotePairs();

	nTracks = file.getTrackCount();
	indices.resize(nTracks);

	sampler.setup();

	allocateSamples();

	sampler.openStream();

	/*
	sampler.newSample('a',1);
	sampler.record('a');
	sampler.play('a', 5);
	*/
}

void FugueSampler::update(unsigned long long tick) {
	for(unsigned track=0; track < nTracks; track++) {
		unsigned index = indices.at(track);
		if(file.getEventCount(track) > index) {
			if(file[track][index].isNoteOn()) {
				MidiEvent event = file.getEvent(track, index);
				float duration = file[track][index].getDurationInSeconds();
				if(event.tick < tick) {
					const char name = event.at(1);

					if(sampler.isRecorded(name)) {
						sampler.play(name, duration);
					} else {
						sampler.record(name);
						cout << "REC" << endl;
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
		}
	}
}

void FugueSampler::ampDetect() {
	sampler.getAmplitude();
}

//----------------------------------------------------------------
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

				bool isPresent = find(cache.begin(), cache.end(), event)
					!= cache.end();

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
