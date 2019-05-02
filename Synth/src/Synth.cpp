#include <unordered_map>
#include <string>
#include <iostream>
#include "streams/SynthesizerStream.h"
#include "streams/Stream.h"
#include "lexer/Parser.h"
#include "Audio.h"

using namespace stk;

namespace tools {
	bool is_number(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}
}

namespace Synth {

	class Synth {

	public:
		//constructor, destructor
		Synth(): streamIDs(new unordered_map<std::string, Stream*>()), audio(Audio(streamIDs)), parser(Parser()) {}
		~Synth() { 
			for (auto it = streamIDs->begin(); it != streamIDs->end(); it++) {
				delete it->second;
			}
			delete streamIDs;  
		}

		void TerminalInterpreter() {
			cout << "Welcome to Synth!" << endl;
			while (1) { //aqui algo debe de haber por si hay un fatal error
				cout << ">>";

				//get the next line
				std::string line;
				std::getline(cin, line);

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
			//TODO: Pedro
		}

		//methods
		Parser& getParser() {
			return parser;
		}

		Audio& getAudio() {
			return audio;
		}

		unordered_map<std::string, Stream*>* getIDs() {
			return streamIDs;
		}
		
	private:
		unordered_map<std::string, Stream*>* streamIDs;
		Parser parser;
		Audio audio;

		//evaluates the line, returns 0 if there was no error, other wise return error code
		int evaluate(ParsedResult* pr) {
			if (pr->error == 0) {
				int error = 0;
				//HERE GOES ALL THE HARD CODED FUNCTIONALITY
				switch (pr->typeOfStatement) {

				case 0: { 
					Stream* stream;
					string typeOfStream = pr->params->at(0);

					if (typeOfStream == "Synthesizer") {
						stream = new SynthesizerStream;
						streamIDs->insert(pair<string, Stream*>(pr->ID, stream));
						error = 0;
					}

					else if (typeOfStream == "Audio") {
						stream = new SynthesizerStream;
						streamIDs->insert(pair<string, Stream*>(pr->ID, stream));

						error = 0;
					}
				}
				case 1: { //Modification
					//TODO: Tua & Jaime

					/*
						MODIFIER FUNCTIONS

						<Synthesizer only> setFrequency(number)
						<Synthesizer only> setAmplitude(number)
						<Synthesizer only> setWave(Sine | Saw | Square)


						
					*/


					break;
				}
				case 2: { //General Statement
					//TODO: Tua & Jaime
					/*
						GENERAL FUNCTIONS

						play(stream, number)
						play(stream)
						pause(stream)
						removeStream(stream)
					*/

					Stream* stream = (SynthesizerStream*)streamIDs->at(pr->ID);
					if (pr->function == "play") {
						if (tools::is_number(pr->params->at(0))) {
							int duration = std::stoi(pr->params->at(0));
							stream->play(duration);
							error = 0;
							break;
						}
						else {
							stream->play(100000);
							error = 0;
							break;
						}
						error = 1;
						break;
					}
					else if (pr->function == "pause") {
						stream->pause();
						error = 0;
						break;
					}
					else if (pr->function == "removeStream") {
						//streamIDs->erase(stream);
						error = 0;
						break;
					}
					else
						error = 1;
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
		//TODO: Gabriel
	};
}


int synthTest3() {
	Synth::Synth s;

	Synth::Stream* synth = new Synth::SynthesizerStream();
	string ahh = "ahh";

	s.getIDs()->insert(pair<std::string, Synth::Stream*>(ahh, synth));

	((Synth::SynthesizerStream*) synth)->addSine(stk::SineWave());
	//((Synth::SynthesizerStream*) synth)->setFrequency(440);
	Sleep(1000);
	synth->play(4);
	
	cin.get();


	return 0;
}

int main(int argc, char** argv) {
	//Synth::Synth synth;
	//argc == 1 ? synth.TerminalInterpreter() : synth.FileInterpreter(argc, argv);
	synthTest3();
}



