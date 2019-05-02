#pragma once
#include "Stream.h"
#include "RtwvOut.h"
#include "SineWave.h"

namespace Synth {
	class AudioInputStream : public Stream
	{
	public:
		AudioInputStream();
		~AudioInputStream();
		void startRTAudio();
		void stopRTAudio();
		virtual float tick();
	private:
		stk::RtWvOut voice;
	};
}

