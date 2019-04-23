#include "Parser.h"
#include <iostream>

namespace Synth {

	ParsedResult::ParsedResult() : params(new vector<string>()) { }

	ParsedResult::~ParsedResult() {
		delete params;
	}


	//processes one line of Synth code
	ParsedResult* Parser::process(string& string) {
		parser_helper ph;
		ParsedResult* pr = new ParsedResult();

		//check if the lexer tokenized well
		if (!ph.init(string)) { pr->error = true; return pr; }
		
		//check the first token
		if (ph.token_is(token::e_symbol, "InitStream", ph.e_hold)) { //INITSTREAM
			pr->function = pr->typeOfStatement = ph.current_token().value;
			ph.advance_token(ph.e_advance);

			if (!ph.token_is_then_assign(token::e_symbol, pr->ID)) {
				pr->error = true; 
				return pr;
			}

			if (!ph.token_is(token::e_symbol, "as")) {
				pr->error = true;
				return pr;
			}

			if (!ph.token_is_then_assign(token::e_symbol, *pr->params)) {
				pr->error = true;
				return pr;
			}
		
			//check if there are more tokens in the lexer
			if (!(ph.lexer().finished()) || 
				!(ph.current_token().value == "")) {
				pr->error = true;
				return pr;
			}
	
		}
		else if (ph.token_is(token::e_symbol, "As", ph.e_hold)) { //MODIFICATION

			
			if (!ph.token_is_then_assign(token::e_symbol, pr->ID)) { // checking streamID
				pr->error = true;
				return pr;
			}


			if (!ph.token_is_then_assign(token::e_symbol, pr->function)) { // checking functions
				pr->error = true;
				return pr;
			}


			if (!ph.token_is(token::e_lbracket)) { // checking left bracket
				pr->error = true;
				return pr;
			}

			if (!ph.token_is(token::e_rbracket)) { // has correct parameters check
				if (!ph.token_is_then_assign(token::e_symbol, *pr->params)) {
					pr->error = true;
					return pr;
				}

				// checking any additional parameters
				while (!ph.peek_token_is(token::e_rbracket) &&
					!ph.lexer().finished()) {
					if (!ph.token_is(token::e_comma) || (!ph.token_is(token::e_number)) || !ph.token_is_then_assign(token::e_symbol, *pr->params)) {
						pr->error = true;
						return pr;
					}
				}

				if (!ph.token_is(token::e_rbracket)) { 
					pr->error = true;
					return pr;
				}
			}

			if (!(ph.lexer().finished()) ||
				!(ph.current_token().value == "")) { // check ends
				pr->error = true;
				return pr;
			}

		}

		//General Function Check
		else if (ph.token_is(token::e_symbol, ph.e_hold)) { //GENERAL STATEMENT
			pr->function = ph.current_token().value;
			ph.advance_token(ph.e_advance);

			//LeftPar Check
			if (!ph.token_is(token::e_lbracket)) {
				pr->error = true;
				return pr;
			}

			//Has Param Check
			if (!ph.token_is(token::e_rbracket)) {
				if (!ph.token_is_then_assign(token::e_symbol, *pr->params)) {
					pr->error = true;
					return pr;
				}

				//Extra Params Check
				while (!ph.peek_token_is(token::e_rbracket) &&
					!ph.lexer().finished()) {
					if (!ph.token_is(token::e_comma)) {
						pr->error = true;
						return pr;
					}
					if (!ph.token_is_then_assign(token::e_symbol, *pr->params)) {
						pr->error = true;
						return pr;
					}
				}

				//RightPar Check
				if (!ph.token_is(token::e_rbracket)) {
					pr->error = true;
					return pr;
				}
			}

			//End Check
			if (!(ph.lexer().finished()) ||
				!(ph.current_token().value == "")) {
				pr->error = true;
				return pr;
			}

		}
		else { //error
			pr->error = true;
		}

		pr->error = false;
		return pr;
	}

}