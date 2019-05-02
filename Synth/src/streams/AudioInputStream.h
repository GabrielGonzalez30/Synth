#pragma once
#include "Stream.h"
#include "RtwvOut.h"

namespace Synth {
	class AudioInputStream : Stream
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

