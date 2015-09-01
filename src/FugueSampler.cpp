#include "FugueSampler.h"

void FugueSampler::setup(string fileName) {
	file.read(fileName);
	if(!file.status()) {
		cerr << "Error reading MIDI file" << endl;
	}

	file.doTimeAnalysis();
	file.linkNotePairs();

	trackCount = file.getTrackCount();
	indices.resize(trackCount);

	sampler.setup();

	/*
	sampler.newSample('a',1);
	sampler.openStream();
	sampler.record('a');
	sampler.play('a', 5);
	sampler.closeStream();
	*/

//	const unsigned uniqueEventCount = getUniqueEventCount();
//	cout << "Unique event count is " << uniqueEventCount << endl;
}

void FugueSampler::update(unsigned long long tick) {
	for(unsigned track=0; track < trackCount; track++) {
		unsigned index = indices.at(track);
		if(file.getEventCount(track) > index) {
			if(file[track][index].isNoteOn()) {
				MidiEvent event = file.getEvent(track, index);
				float duration = file[track][index].getDurationInSeconds();
				if(event.tick < tick) {
					cout << tick << "  Found event "
						<< (unsigned)event.at(1)
						<< " with duration "
						<< duration
						<< endl;

					indices.at(track)++;
				}
			} else {
				indices.at(track)++;
			}
		}
	}
}

//----------------------------------------------------------------
unsigned FugueSampler::getUniqueEventCount() {
	vector< vector<unsigned char> > cache;
	cout << "Eventcount is " << file.getEventCount(0) << endl;

	for(int i=0; i<file.getEventCount(0); i++) {
		if(file[0][i].isNoteOn()) {
			cout << "Getting event " << i;

			cout << "(";
			vector<unsigned char> event;
			for(auto m : file[0][i]) {
				cout << (unsigned) m << " ";
				event.push_back(m);
			}
			cout << ")" << endl;

			bool isPresent = find(cache.begin(), cache.end(), event)
				!= cache.end();

			if(!isPresent) {
				cache.push_back(event);
				cout << (unsigned)event[1] << " is unique!" << endl;
			}
		}
	}

	return cache.size();
}
