#include "Parser.h"

namespace Synth {

	//processes one line of Synth code
	bool Parser::process(string& string) {
		parser_helper ph;

		//check if lexer can recognize the tokens
		if (!ph.init(string)) { return false; }
		
	}

}