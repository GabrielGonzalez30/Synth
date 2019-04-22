#pragma once

#include "lexertk.h"
#include <string>

using namespace std;
using namespace lexertk;

namespace Synth {

	class Parser {

	public:
		bool process(string& string);

	private:
		bool processAssign();
		bool processStatement();


	};
}