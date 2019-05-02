#pragma once
#include "RtAudio.h"
#include "Stk.h"
#include "streams/Stream.h"
#include <unordered_map>

using namespace std;

namespace Synth {

	inline int calcSound(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void* data);

	class Audio {
	public:
		Audio(unordered_map<std::string, Stream*>* streamIDs);
		Audio(unordered_map<std::string, Stream*>* streamIDs, int sampleRate, int bufferRate);
		~Audio();

		void startStream();
		void stopStream();


	private:
		unsigned int sampleRate;
		unsigned int bufferFrames;
		unsigned int bufferBytes;
		RtAudio engine;
		RtAudio::StreamParameters iParams, oParams;

		unordered_map<std::string, Stream*>* streamIDs;

		inline bool hasAudioDevices();

		inline void openAudioStream();
		inline void closeAudioStream();

		//int calcSound(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
			//double streamTime, RtAudioStreamStatus status, void* data);



	};

	

}