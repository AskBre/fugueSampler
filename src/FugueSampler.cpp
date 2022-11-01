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

	ticksPerQuarterNote = file.getTicksPerQuarterNote();
	cout << "TPQN is " << ticksPerQuarterNote << endl;

	// Iterate through to the tempo-message
	for(unsigned t=0; t<file.getTrackCount(); t++) {
		for(unsigned e=0; e<file.getEventCount(t); e++) {
			if(file[t][e].isTempo()) {
				beatsPerMinute = file[t][e].getTempoBPM();
				cout << "BPM is " << beatsPerMinute << endl;
			}
		}
	}

	//Set default BPM
	if(!beatsPerMinute) beatsPerMinute = 120;

	double dur = 1.0f / (beatsPerMinute/60 * ticksPerQuarterNote);
	cout << "DUR " << dur << endl;
	tickDuration = (chrono::duration<double>) dur;
	cout << "TICKLENGHT " << tickDuration.count() << endl;
	prevTickTime = chrono::system_clock::now();

	nTracks = file.getTrackCount();
	indices.resize(nTracks);

	sampler.setup();

	allocateSamples();

	sampler.openStream();
}

void FugueSampler::update() {
	chrono::time_point<chrono::high_resolution_clock> curTime;
	curTime = chrono::system_clock::now();

	chrono::duration<double> deltaPrevTick =  curTime - prevTickTime;

	if(deltaPrevTick > tickDuration) {
		if(runState == RUN) {
			recAndPlay(tick);
			tick++;
		} else if(runState == REACHED_END) {
			tick = 0;
			runState = RUN;
		} else if (runState == STOPPED) {
			exit(0);
		}
		prevTickTime = curTime;
	}

}

void FugueSampler::ampDetect() {
	double amp = sampler.getAmplitude();
	cout << amp << endl;
	if(amp > THRES) {
		runState = RUN;
	}

	// If debugging without audio input
//	runState = RUN;
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
					curSampleName = event.at(1);

					if(sampler.isRecorded(curSampleName)) {
						sampler.play(curSampleName, duration);
						cout << "Playing " << curSampleName << endl;
					} else {
						sampler.record(curSampleName);
						cout << "Recording " << curSampleName << endl;
					}

					indices.at(track)++;
					eventCounter++;

					unsigned percent =
						(float)eventCounter/(float)nEvents*100;
					if(percent!=oldPercent) {
//						cout << percent << "%" << endl;
					}

					oldPercent = percent;
				}
			} else {
				indices.at(track)++;
			}
		} else if (shouldLoop && index > nEvents && !sampler.isPlaying(curSampleName)) {
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
