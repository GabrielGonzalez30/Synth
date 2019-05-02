#include "AudioFileStream.h"

namespace Synth {

	AudioFileStream::AudioFileStream(): f_index(0)
	{
	}


	AudioFileStream::~AudioFileStream()
	{
	}

	void AudioFileStream::addAudioFile(std::string f) {
		stk::FileLoop track;
		track.openFile(f);
	}

	float AudioFileStream::tick() {
		float total = 0;
		for (unsigned int i = 0; i < f_index; i++) {
			total += files[i].tick();
		}
		return total / f_index;
		//TODO check div 0
	}

	void AudioFileStream::removeAudioFile(int i) {
		//TODO add validation
		files[i].closeFile();
		for (int j = i; j < f_index; j++) {
			files[j] = files[j + 1];
		}
		f_index--;
	}
}
