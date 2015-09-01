#pragma once

#include "RtAudio.h"
#include <iostream>
#include <string.h>
#include <algorithm>

#include "FugueSampler.h"
#include "SamplerSample.h"

#define SAMPLE_RATE 48000
#define BUFFER_FRAMES 256

using namespace std;

class Sampler : public FugueSampler {
	public:
		void setup();
		void newSample(const char sampleName, const float sampleLengthInSec);
		void openStream();
		void closeStream();
		void record(const char sampleName);
		void play(const char sampleName, const float seconds);

	private:
		RtAudio audio;
		RtAudio::StreamParameters iParams, oParams;
		vector<SamplerSample> samples;

		int getSampleIndex(const char &name);
};

int recAndPlay(void *outputBuffer, void *inputBuffer,
		unsigned int nBufferFrames, double streamTime,
		RtAudioStreamStatus status, void *userData);
