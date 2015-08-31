#pragma once

#include "RtAudio.h"
#include <iostream>
#include <string.h>
#include <algorithm>

#include "SamplerTrack.h"

#define SAMPLE_RATE 48000
#define BUFFER_FRAMES 256

using namespace std;

class Sampler {
	public:
		void setup();
		void newTrack(const char trackName, const float trackLengthInSec);
		void openStream();
		void closeStream();
		void record(const char trackName);
		void play(const char trackName, const float seconds);

	private:
		RtAudio audio;
		RtAudio::StreamParameters iParams, oParams;
		vector<SamplerTrack> tracks;

		int getTrackIndex(const char &name);


};

int recAndPlay(void *outputBuffer, void *inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void *userData);

