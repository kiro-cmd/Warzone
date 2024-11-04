#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>

using namespace std;

class GameEngine {
	public:
		int* statesCount;
		string* current = new string("");
		string* states = new string[0];
		// This matrix specifies the commands needed to go from one command to the other.
		//   - n is the number of states.
		//   - There are n + 1 rows and n columns.
		//     - The extra row is to specify a command to end the program from a given state.
		//   - commands[i][j] is the command to go from state i to state j.
		//   - If commands[i][j] == "", then no transition is possible from state i to state j.
		string** commands = new string*[0];
		
		GameEngine();
		
		bool transition(string command);
};
#endif // GAMEENGINE_H