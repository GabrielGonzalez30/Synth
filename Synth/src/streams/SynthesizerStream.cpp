#include "SynthesizerStream.h"



namespace Synth {


	SynthesizerStream::SynthesizerStream() : s_index(0), sq_index(0), t_index(0) {}
	SynthesizerStream::~SynthesizerStream() {}

	void SynthesizerStream::addSine(float f) {
		stk::SineWave s;
		s.setFrequency(f);
		sine_waves[s_index] = s;
		s_index++;
	}

	void SynthesizerStream::addSqrt(float f) {
		stk::BlitSquare b;
		b.setFrequency(f);
		sqrt_waves[sq_index] = b;
		sq_index++;
	}

	void SynthesizerStream::addTrig(float f) {
		stk::BlitSaw b;
		b.setFrequency(f);
		trig_waves[t_index] = b;
		t_index++;
	}

	float SynthesizerStream::tick() {
		float total = 0;
		for (unsigned int i = 0; i < s_index; i++) {
			total += sine_waves[i].tick();

		}
		for (unsigned int i = 0; i < sq_index; i++) {
			total += sqrt_waves[i].tick();

		}
		for (unsigned int i = 0; i < t_index; i++) {
			total += trig_waves[i].tick();

		}
		if ((s_index + sq_index + t_index) == 0)
			return 0;
		return total / (s_index + sq_index + t_index);
	}

};