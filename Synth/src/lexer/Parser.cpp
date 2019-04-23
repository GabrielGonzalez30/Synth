#include "Parser.h"
#include <iostream>

namespace Synth {

	ParsedResult::ParsedResult() : params(new vector<string>()), error(0) { }

	ParsedResult::~ParsedResult() {
		delete params;
	}

	//processes one line of Synth code
	ParsedResult* Parser::process(string& string) {
		
		current_result = new ParsedResult();

		//check if the lexer tokenized well
		if (!ph.init(string)) { current_result->error = true; return current_result; }
		current_string = string;
		
		int error;
		//check the first token
		if (ph.token_is(token::e_symbol, "InitStream", ph.e_hold)) { //INITSTREAM
			error = processInitStream();
		}
		else if (ph.token_is(token::e_symbol, "As", ph.e_hold)) { //MODIFICATION
			error = processModification();
		}
		//General Function Check
		else if (ph.token_is(token::e_symbol, ph.e_hold)) { //GENERAL STATEMENT
			error = processGeneralStatement();
		}
		else { //error
			error = syntaxError;
		}

		ph.clear();
		current_result->error = error;
		return current_result;
	}

	int Parser::processInitStream() {
		current_result->function = current_result->typeOfStatement = ph.current_token().value;
		ph.advance_token(ph.e_advance);

		if (!ph.token_is_then_assign(token::e_symbol, current_result->ID)) {
			return syntaxError;
		}

		if (!ph.token_is(token::e_symbol, "as")) {
			return syntaxError;
		}

		if (!ph.token_is_then_assign(token::e_symbol, *(current_result->params))) {
			return paramsError;
		}

		//check if there are more tokens in the lexer
		if (!(ph.lexer().finished()) ||
			!(ph.current_token().value == "")) {
			return syntaxError;
		}

		return none;
	}

	int Parser::processModification() {
		current_result->typeOfStatement = "Modification";
		ph.advance_token(ph.e_advance);

		if (!ph.token_is_then_assign(token::e_symbol, current_result->ID)) { // checking streamID
			return syntaxError;
		}

		if (!ph.token_is_then_assign(token::e_symbol, current_result->function)) { // checking functions
			return syntaxError;
		}


		if (!ph.token_is(token::e_lbracket)) { // checking left bracket
			return syntaxError;
		}

		while (!(ph.lexer().finished())) {

			if (!(ph.token_is_then_assign(token::e_number, *current_result->params) ||
				ph.token_is_then_assign(token::e_symbol, *current_result->params))) {
				return paramsError;
			}
			
			if (ph.token_is(token::e_rbracket)) {
				break;
			}

			if (!ph.token_is(token::e_comma)) {
				return syntaxError;
			}
				
		}

		if (!(ph.lexer().finished()) ||
			!(ph.current_token().value == "")) { // check ends
			return syntaxError;
		}

		return none;
	}

	int Parser::processGeneralStatement() {
		current_result->function = ph.current_token().value;
		ph.advance_token(ph.e_advance);

		//LeftPar Check
		if (!ph.token_is(token::e_lbracket)) {
			return syntaxError;
		}

		//Has Param Check
		while (!(ph.lexer().finished())) {

			if (!(ph.token_is_then_assign(token::e_number, *current_result->params) ||
				ph.token_is_then_assign(token::e_symbol, *current_result->params))) {
				return paramsError;
			}

			if (ph.token_is(token::e_rbracket)) {
				break;
			}

			if (!ph.token_is(token::e_comma)) {
				return syntaxError;
			}

		}

		//End Check
		if (!(ph.lexer().finished()) ||
			!(ph.current_token().value == "")) {
			return syntaxError;
		}

		return none;
	}

}