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

		void setFrequency(float number);

		

	private:
		stk::SineWave sine_waves[50]; //Assumes 50 is more than enought.
		stk::BlitSquare sqrt_waves[50];
		stk::BlitSaw trig_waves[50];

		int s_index;
		int sq_index;
		int t_index;
	};
}