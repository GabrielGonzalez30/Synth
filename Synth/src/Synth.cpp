#include <unordered_map>
#include <string>
#include <iostream>
#include <cstdlib>
#include "RtWvOut.h"
#include "streams/SynthesizerStream.h"
#include "lexer/Parser.h"
#include "Audio.h";

using namespace std;
using namespace stk;

namespace Synth {

	class Synth {

	public:
		//constructor, destructor
		Synth(): streamIDs(new unordered_map<string, Stream*>()), audio(Audio()), parser(Parser()) {}
		~Synth() { delete streamIDs; }

		void TerminalInterpreter() {
			cout << "Welcome to Synth!" << endl;
			while (1) { //aqui algo debe de haber por si hay un fatal error
				cout << ">" << endl;

				//get the next line
				string line;
				getline(cin, line);

				//parse the line
				ParsedResult* pr = parser.process(line);

				//execute the line
				int error = evaluate(pr);
				if (error > 0) {
					handleError(error);
				}

				//free parsed result
				delete pr;
			}
		}

		void FileInterpreter(int argCounter, char** arguments) {
			//TODO
		}

		//methods
		Parser& getParser() {
			return parser;
		}

		Audio& getAudio() {
			return audio;
		}
		
	private:
		unordered_map<string, Stream*>* streamIDs;
		Parser parser;
		Audio audio;

		//evaluates the line, returns 0 if there was no error, other wise return error code
		int evaluate(ParsedResult* pr) {
			if (pr->error == 0) {
				int error = 0;
				//HERE GOES ALL THE HARD CODED FUNCTIONALITY
				switch (pr->typeOfStatement) {

				case 0: { //InitStream

					break;
				}
				case 1: { //Modification

					break;
				}
				case 2: { //General Statement

					break;
				}
				default:
					break;
				}

				return error;
			} 
			else {
				return pr->error;
			}
		}
		void handleError(int error) {

		}
	};

	struct SynthError {
		//TODO
	};
}


int synthTest() {
	// Set the global sample rate before creating class instances.
	Stk::setSampleRate(44100.0);
	Stk::showWarnings(true);
	int nFrames = 100000;
	RtWvOut* dac = 0;

	try {
		// Define and open the default realtime output device for one-channel playback
		dac = new RtWvOut(1);
	}
	catch (StkError&) {
		exit(1);
	}

	//Adding 3 sine waves
	SineWave* s = new SineWave();
	s->setFrequency(440);
	Synth::SynthesizerStream track;
	track.addSine(*s);
	s->setFrequency(220);
	track.addSine(*s);
	s->setFrequency(880);
	track.addSine(*s);



	//Playing
	for (int i = 0; i < nFrames; i++) {
		try {
			dac->tick(track.tick());
		}
		catch (StkError&) {
			goto cleanup;
		}
	}

	goto cleanup;

cleanup:
	delete dac;
	delete s;
	return 0;
}
int synthTest2() {
	Synth::Synth s;
	Synth::SynthesizerStream synth;
	Synth::SynthesizerStream otherSynth

	synth.addSine(200);
	synth.addSqrt(300);
	otherSynth.addTrig(600);

	s.getAudio().addStream(synth);
	s.getAudio().addStream(otherSynth);

	s.getAudio().startStream();

	cin.get();

	s.getAudio().stopStream();

	return 0;
}

int main(int argc, char** argv) {
	synthTest2();
	//Synth::Synth synth;
	//argc == 1 ? synth.TerminalInterpreter() : synth.FileInterpreter(argc, argv);
}



