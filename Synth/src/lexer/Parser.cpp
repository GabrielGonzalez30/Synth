#include "Parser.h"

namespace Synth {

	ParsedResult::ParsedResult() : params(new vector<string>()) { }

	ParsedResult::~ParsedResult() {
		delete params;
	}


	//processes one line of Synth code
	ParsedResult* Parser::process(string& string) {
		parser_helper ph;
		ParsedResult* pr = new ParsedResult;

		//check if the lexer tokenized well
		if (!ph.init(string)) { pr->error = true; return pr; }
		

		//check the first token
		if (ph.token_is(token::e_symbol, "InitStream", ph.e_hold)) { //INITSTREAM
			ph.advance_token(ph.e_advance);
			//define init stream grammar
		}
		else if (ph.token_is(token::e_symbol, "As", ph.e_hold)) { //MODIFICATION
			ph.advance_token(ph.e_advance);
			//define modification grammar
		}
		else if (ph.token_is(token::e_symbol, ph.e_hold)) { //GENERAL STATEMENT
			ph.advance_token(ph.e_advance);
			//define general statement grammar
		}
		else { //error
			pr->error = true;
		}

		return pr;
	}

}