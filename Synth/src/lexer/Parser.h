#pragma once

#include "lexertk.h"
#include <string>

using namespace std;
using namespace lexertk;

namespace Synth {

	/*
		*Define the grammar
		InitializeStream: InitStream [streamID] as [Type]
		StreamModification: [streamID] [Function]([Parameters]) 
		GeneralStatement: [Function]([Parameters])

		**Stream Modifier Functions**
		play:
		stop:
		setFrequency:
		setAmplitude:
		add:
		filter:
		saveOnRecord:
		....etc....




	*/

	class Parser {

	public:
		//processes one line of Synth code
		bool process(string& string);

	private:
		bool processAssign();
		bool processStatement();


	};
}