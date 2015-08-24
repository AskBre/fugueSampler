#pragma once

#include "RtAudio.h"
#include <iostream>
#include <string.h>
#include <algorithm>

#define SAMPLE_RATE 48000
#define BUFFER_FRAMES 256

using namespace std;

enum state_t {STOP, REC, PLAY};

struct track_t {
	char name;
	state_t state = STOP;
	double *buffer;
	unsigned bufferSize;
	unsigned iteration = 0;
};

class Sampler {
	public:
		int setup();
		int newTrack(const char name, const float seconds);
		int openStream();
		int closeStream();
		int record(const char trackName);
		int play(const char trackName, const float seconds);

	private:
		RtAudio audio;
		RtAudio::StreamParameters iParams, oParams;
		vector<track_t> tracks;

};

int recAndPlay(void *outputBuffer, void *inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void *userData);
