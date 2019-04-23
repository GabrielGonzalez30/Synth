#include <unordered_map>
#include <string>
#include <iostream>
#include "streams/Stream.h"
#include "lexer/Parser.h"

using namespace std;

namespace Synth {

	class Synth {

	public:
		//constructor, destructor
		Synth(): streamIDs(new unordered_map<string, Stream*>()) {}
		~Synth() { delete streamIDs; }

		//instance variables
		Parser parser;

		//methods
		//void Interpreter();
		

	private:
		unordered_map<string, Stream*>* streamIDs;
		//SynthError* evaluate(string& line);
		//void handleError(SynthError& error);
	};

	/*struct SynthError {

	};*/
}



int main() {

	Synth::Synth s;

	while (1) {
		//get the next line

		//parse the line

		//check what function does it need to do

		//execute function

		//free parsed result


		cout << ">> ";
		string line;
		getline(cin, line);

		auto theLine = s.parser.process(line);

		cout << "Function: " << theLine->function << endl;
		cout << "Type Of Statement: " << theLine->typeOfStatement << endl;
		cout << "ID: " << theLine->ID << endl;
		cout << "Params: " << theLine->params->size() << endl;
		cout << "Error: " << (theLine->error > 0 ? "true" : "false") << endl;

		delete theLine;
	}
}