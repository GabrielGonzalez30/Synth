#pragma once
#include "RtAudio.h"
#include "Stk.h"
#include "streams/Stream.h"
#include <unordered_map>
#include <queue>
#include <memory>

using namespace std;

namespace Synth {

	inline int calcSound(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void* data);

	struct CalcSoundData {
		//queue<pair<string, shared_ptr<Stream>>>* aQueue;
		queue<string>* dQueue;
		unordered_map<string, shared_ptr<Stream>>* sIDs;

		CalcSoundData() : dQueue(nullptr), sIDs(nullptr) {}
	};

	class Audio {
	public:
		Audio(unordered_map<std::string, std::shared_ptr<Stream>>* streamIDs);
		Audio(unordered_map<std::string, std::shared_ptr<Stream>>* streamIDs, int sampleRate, int bufferRate);
		~Audio();

		void startStream();
		void stopStream();

		void setForDeletion(string& streamID) {
			deleteQueue.push(streamID);
		}
		/*void setForAddition(string& streamID, shared_ptr<Stream> stream) {
			addQueue.push(pair<string, shared_ptr<Stream>>(streamID, stream));
		}
		*/

	private:
		unsigned int sampleRate;
		unsigned int bufferFrames;
		unsigned int bufferBytes;

		queue<string> deleteQueue;
		//queue <pair<string, shared_ptr<Stream>>> addQueue;
		CalcSoundData data;
		RtAudio engine;
		RtAudio::StreamParameters iParams, oParams;
		unordered_map<std::string, std::shared_ptr<Stream>>* streamIDs;

		inline bool hasAudioDevices();

		inline void openAudioStream();
		inline void closeAudioStream();


	};

	

}