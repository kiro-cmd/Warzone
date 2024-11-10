#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>

#include "CommandProcessor.cpp"

using namespace std;

class GameEngine {
	public:
		bool* running = new bool(false);
		int* statesCount;
		string* current = new string("");
		string* states = new string[0];
		// This matrix specifies the commands needed to go from one state to the other.
		//   - n is the number of states.
		//   - There are n + 1 rows and n columns.
		//     - The extra row is to specify a command to end the program from a given state.
		//   - commands[i][j] is the command to go from state i to state j.
		//   - If commands[i][j] == "", then no transition is possible from state i to state j.
		bool** canTrans = new bool*[0];
		
		CommandProcessor* cp = new CommandProcessor();
		
		GameEngine();
		
		~GameEngine();
		
		void command();
		
		int getStateIndex(string state);
		
		bool transition(string command);
};
#endif // GAMEENGINE_H