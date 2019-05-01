#include "Audio.h"

namespace Synth {

	Audio::Audio(Synth* synthRef) : Audio(synthRef, 48000, 512) {
	}

	Audio::Audio(Synth* synthRef, int sampleRate, int bufferFrames) :
				synthRef(synthRef),
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
		}

	}

	Audio::~Audio() {
	}

	inline void Audio::openAudioStream() {
		if (!engine.isStreamOpen()) {
			engine.openStream(&oParams, NULL, RTAUDIO_FLOAT64, sampleRate, &bufferFrames, calcSound, synthRef->getIDs());
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
		vector<Stream*>* streams = (vector<Stream*>*) data;
		stk::FLOAT64* out = (stk::FLOAT64*) outputBuffer;
		//if (status) std::cout << "Stream over/underflow detected." << std::endl;


		//calculate new buffer
		for (int i = 0; i < nBufferFrames; i++) {
			//get the sounds from the streams
			float sum = 0;
			for (Stream* s : *streams) {
				if (s->shouldPlay(streamTime)) {
					sum += s->tick();
				}
			}

			sum /= streams->size();


			out[i] = sum;
		}

		return 0;

	}

	


}