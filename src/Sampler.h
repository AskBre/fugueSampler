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
		int setup();
		int newTrack(const char trackName, const float trackLengthInSec);
		int openStream();
		int closeStream();
		int record(const char trackName);
		int play(const char trackName, const float seconds);

	private:
		RtAudio audio;
		RtAudio::StreamParameters iParams, oParams;
		vector<SamplerTrack> tracks;

		int getTrackIndex(const char &name);


};

int recAndPlay(void *outputBuffer, void *inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void *userData);

