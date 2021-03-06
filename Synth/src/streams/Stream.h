#pragma once

namespace Synth {
	class Stream
	{
	public:
		int currentTime;
		int stopTime;

		bool shouldPlay(int time) {
			currentTime = time;
			return stopTime > currentTime;
		}

		void play(int duration) {
			stopTime = currentTime + duration;
		}

		void pause() {
			stopTime = 0;
		}

		virtual float tick();

	};
}

