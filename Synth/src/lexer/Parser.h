#pragma once

#include "lexertk.h"
#include <string>
#include <vector>

using namespace std;
using namespace lexertk;

namespace Synth {

	struct ParsedResult {
		ParsedResult();
		~ParsedResult();
		string typeOfStatement;
		string function;
		string ID;
		vector<string>* params;
		int error;
	};

	class Parser {

	public:
		//processes one line of Synth code
		ParsedResult* process(string& string);

		enum ParserError
		{
			none = 0, syntaxError, paramsError, //TODO
		};

	private:
		//instace vars
		parser_helper ph;
		string current_string;
		ParsedResult* current_result;

		//helpers
		int processInitStream();
		int processModification();
		int processGeneralStatement();
		

	
	};
}