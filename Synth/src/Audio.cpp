#include "Audio.h"

namespace Synth {

	Audio::Audio(unordered_map<std::string, Stream*>* streamIDs) : Audio(streamIDs, 48000, 512) {
	}

	Audio::Audio(unordered_map<std::string, Stream*>* streamIDs, int sampleRate, int bufferFrames) :
				streamIDs(streamIDs),
				engine(RtAudio()),									   
				sampleRate(sampleRate),										   
				bufferFrames(bufferFrames),										   
				bufferBytes(bufferFrames * 8) {
		if (!hasAudioDevices()) {
			cout << "Warning! No audio devices detected. Synth will not be able to provide Real-Time audio." << endl;
		}
		else {
			//iParams.deviceId = engine->getDefaultInputDevice(); // first available device
			//iParams.nChannels = 1;
			oParams.deviceId = engine.getDefaultOutputDevice();
			oParams.nChannels = 1;
			openAudioStream();
			startStream();
		}

	}

	Audio::~Audio() {
	}

	inline void Audio::openAudioStream() {
		if (!engine.isStreamOpen()) {
			engine.openStream(&oParams, NULL, RTAUDIO_FLOAT64, sampleRate, &bufferFrames, calcSound, streamIDs);
		}
	}

	inline void Audio::closeAudioStream() {
		if (engine.isStreamOpen()) {
			engine.closeStream();
		}
	}

	inline bool Audio::hasAudioDevices() {
		return (engine.getDeviceCount() > 0);
	}

	void Audio::startStream() {
		engine.startStream();
	}

	void Audio::stopStream() {
		engine.stopStream();
	}


	inline int calcSound(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void* data) {

		//setup casts...
		unordered_map<std::string, Stream*>* streams = (unordered_map<std::string, Stream*>*) data;
		stk::FLOAT64* out = (stk::FLOAT64*) outputBuffer;
		//if (status) std::cout << "Stream over/underflow detected." << std::endl;


		//calculate new buffer
		for (int i = 0; i < nBufferFrames; i++) {
			//get the sounds from the streams
			float sum = 0;
			for (auto it = streams->begin(); it != streams->end(); it++) {
				if (it->second->shouldPlay(streamTime)) {
					sum += it->second->tick();
				}
			}
			sum /= streams->size();
			out[i] = sum;
		}
		return 0;

	}

	


}