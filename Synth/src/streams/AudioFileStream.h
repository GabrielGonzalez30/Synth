#pragma once
#include "Stream.h"
#include "FileLoop.h"

namespace Synth {
	class AudioFileStream : Stream
	{
	public:
		AudioFileStream();
		~AudioFileStream();
		void addAudioFile(std::string file);
		void removeAudioFile(int i);
		virtual float tick();
	private:
		stk::FileLoop files[50];//Assume that 50 is more than enought.
		int f_index;
	};
}

