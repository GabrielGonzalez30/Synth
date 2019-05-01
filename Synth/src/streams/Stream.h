#pragma once

namespace Synth {
	class Stream {
	public:
		int currentTime;
		int stopTime;
		
		void play(int duration) {
			stopTime = currentTime + duration;
		}

		bool shouldPlay(int time) {
			if (time > currentTime) {
				currentTime = time;
			}

			return stopTime - currentTime > 0;
		}

		
		virtual float tick();
	};
}

