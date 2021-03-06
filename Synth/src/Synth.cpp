#include <unordered_map>
#include <string>
#include <iostream>
#include "streams/SynthesizerStream.h"
#include "streams/Stream.h"
#include "lexer/Parser.h"
#include "Audio.h"
#include "fstream"
#include <memory>

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
		Synth(): streamIDs(new unordered_map<std::string, std::shared_ptr<Stream>>()), audio(Audio(streamIDs)), parser(Parser()) {}
		~Synth() { 
			delete streamIDs;  
		}

		void TerminalInterpreter() {
			cout << "Welcome to Synth!" << endl;
			int error = 0;
			while (error == 0) { //aqui algo debe de haber por si hay un fatal error
				cout << ">>";

				//get the next line
				std::string line;
				std::getline(cin, line);

				//parse the line
				ParsedResult* pr = parser.process(line);

				//execute the line
				error = evaluate(pr);
				if (error > 0) {
					handleError(error);
				}

				//free parsed result
				delete pr;
			}
		}

		void FileInterpreter(int argCounter, char* argument) {
			std::ifstream infile(argument);
			std:string line;
			ParsedResult* pr;
			int error;
			while(std::getline(infile, line)){
				pr = parser.process(line);
				error = evaluate(pr);
				if (error > 0) {
					handleError(error);
				}
			}
			infile.close();
		}

		//methods
		Parser& getParser() {
			return parser;
		}

		Audio& getAudio() {
			return audio;
		}

		unordered_map<std::string, std::shared_ptr<Stream>>* getIDs() {
			return streamIDs;
		}
		
	private:
		unordered_map<std::string, std::shared_ptr<Stream>>* streamIDs;
		Parser parser;
		Audio audio;

		//evaluates the line, returns 0 if there was no error, other wise return error code
		int evaluate(ParsedResult* pr) {
			if (pr->error == 0) {
				int error = 0;
				//HERE GOES ALL THE HARD CODED FUNCTIONALITY
				switch (pr->typeOfStatement) {

				case Parser::InitStream: { 
					std::shared_ptr<Stream> stream;
					string typeOfStream = pr->params->at(0);

					if (typeOfStream == "Synthesizer") {
						stream = std::make_shared<SynthesizerStream>();
						//audio.setForAddition(pr->ID, stream);
						streamIDs->insert(pair<string, shared_ptr<Stream>>(pr->ID, stream));
						error = 0;
						break;
					}

					else if (typeOfStream == "Audio") {
						stream = std::make_shared<SynthesizerStream>();
						streamIDs->insert(pair<string, shared_ptr<Stream>>(pr->ID, stream));
						error = 0;
						break;
					}
					error = 1;
					break;
				}
				case Parser::Modification: { //Modification
					string  parameters = pr->params->at(0);

					auto ID = std::dynamic_pointer_cast<SynthesizerStream>(streamIDs->at(pr->ID)); // synthesizer ayy lmao

					if (pr->function == "setFrequency") {
						if (tools::is_number(parameters)) {
							float frequency = std::stof(parameters);
							ID->setFrequency(frequency);
							error = 0;
							break;
						}

						else {
							error = 1;
							break;
						}
					}
					if (pr->function == "setWave") {
						if (parameters == "Sine") {
							ID->addSine(200);
							error = 0;
							break;
						}

						if (parameters == "Saw") {
							ID->addTrig(200);
							error = 0;
							break;
						}

						if (parameters == "Square") {
							ID->addSqrt(200);
							error = 0;
							break;
						}

						else {
							error = 1;
							break;
						}
					}

					error = 1;
					break;
				}
				case Parser::GeneralStatement: { //General Statement
					//TODO: Tua & Jaime
					/*
						GENERAL FUNCTIONS

						play(stream, number)
						play(stream)
						pause(stream)
						removeStream(stream)
					*/

					auto stream = std::dynamic_pointer_cast<SynthesizerStream>(streamIDs->at(pr->params->at(0)));
					if (pr->function == "play") {
						if (pr->params->size() == 2) {
							if (tools::is_number(pr->params->at(1))) {
								int duration = std::stoi(pr->params->at(1));
								stream->play(duration);
								sleep(duration*1000);
								error = 0;
								break;
							}
						}
						else if (pr->params->size() == 1) {
							stream->play(100000);
							error = 0;
							break;
						}
						error = 1;
						break;
					}
					else if (pr->function == "pause" && pr->params->size() == 1) {
						stream->pause();
						error = 0;
					}
					else if (pr->function == "removeStream" && pr->params->size() == 1) {
						audio.setForDeletion(pr->params->at(0));
						error = 0;
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

int main(int argc, char** argv) {
	Synth::Synth synth;
	argc == 1 ? synth.TerminalInterpreter() : synth.FileInterpreter(argc, argv[1]);
	//char path[] = "C:\\Users\\Owrn\\Documents\\gitRepos\\PL_Project\\test.syn";
	//synth.FileInterpreter(0, path);
}



