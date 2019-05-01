#pragma once
#include "Stream.h"
#include "SineWave.h"
#include "BlitSquare.h"
#include "BlitSaw.h"


namespace Synth {
	class SynthesizerStream : public Stream {
	public:
		SynthesizerStream();
		~SynthesizerStream();
		void addSine(stk::SineWave s);
		void addSqrt(stk::BlitSquare b);
		void addTrig(stk::BlitSaw b);
		virtual float tick();

		void setFrequency(float number) {
			for (unsigned int i = 0; i < s_index; i++) {
				sine_waves[i].setFrequency(number);
			}
			for (unsigned int i = 0; i < sq_index; i++) {
				sqrt_waves[i].setFrequency(number);
			}
			for (unsigned int i = 0; i < t_index; i++) {
				trig_waves[i].setFrequency(number);
			}
		}

		

	private:
		stk::SineWave sine_waves[50]; //Assumes 50 is more than enought.
		stk::BlitSquare sqrt_waves[50];
		stk::BlitSaw trig_waves[50];

		int s_index;
		int sq_index;
		int t_index;
	};
}