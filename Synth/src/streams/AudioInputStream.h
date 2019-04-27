#pragma once
#include "Stream.h"

namespace Synth {
	class AudioInputStream : public Stream
	{
	public:
		AudioInputStream();
		~AudioInputStream();
		virtual float tick();
	};
}

