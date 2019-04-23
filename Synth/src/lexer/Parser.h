#pragma once

#include "lexertk.h"
#include <string>
#include <vector>

using namespace std;
using namespace lexertk;

namespace Synth {

	/*
		*Define the grammar
		InitializeStream: InitStream [streamID] as [Type]

		InputAudio, AudioFile, Synthesizer

		StreamModification: As [streamID] [Function]([Parameters]) 
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

		alskjdflfajskd(1, 2, 3)


	*/

	struct ParsedResult {
		ParsedResult();
		~ParsedResult();
		string typeOfStatement;
		string function;
		string ID;
		vector<string>* params;
		bool error; //true if error
	};

	class Parser {

	public:
		//processes one line of Synth code
		ParsedResult* process(string& string);
	
	};
}