#pragma once
#include "RtAudio.h"
#include "Stk.h"
#include "streams/Stream.h"
#include <vector>
#include "Synth.cpp"

using namespace stk;
using namespace std;

namespace Synth {

	inline int calcSound(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void* data);

	class Audio {
	public:
		Audio(Synth * synthRef);
		Audio(Synth * synthRef, int sampleRate, int bufferRate);
		~Audio();

		void addStream(Stream& s);
		//inline void removeStream(Stream& s);

		void startStream();
		void stopStream();


	private:
		unsigned int sampleRate;
		unsigned int bufferFrames;
		unsigned int bufferBytes;
		Synth* synthRef;
		RtAudio engine;
		RtAudio::StreamParameters iParams, oParams;
		vector<Stream*> streams;

		inline bool hasAudioDevices();

		inline void openAudioStream();
		inline void closeAudioStream();

		//int calcSound(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
			//double streamTime, RtAudioStreamStatus status, void* data);



	};

	

}