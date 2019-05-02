#include "AudioInputStream.h"

namespace Synth {
	AudioInputStream::AudioInputStream():voice(0)
	{
		
	}


	AudioInputStream::~AudioInputStream()
	{
	}

	void AudioInputStream::startRTAudio() {
		voice =  stk::RtWvOut(1);
	}

	void AudioInputStream::stopRTAudio() {
		voice = stk::RtWvOut(1);
		voice.stop();
		voice = 0;
	}

	float AudioInputStream::tick() {
		return voice.tick();
	}
}
