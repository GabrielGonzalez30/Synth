#pragma once
#include "Stream.h"

namespace Synth {
	class AudioFileStream : public Stream
	{
	public:
		AudioFileStream();
		~AudioFileStream();
		virtual float tick();
	};
}

