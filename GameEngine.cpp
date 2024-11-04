#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine() {
	statesCount = new int(8);
	
	states = new string[*statesCount];
	states[0] = "start";
	states[1] = "map loaded";
	states[2] = "map validated";
	states[3] = "players added";
	states[4] = "assign reinforcement";
	states[5] = "issue orders";
	states[6] = "execute orders";
	states[7] = "win";
	
	commands = new string*[*statesCount];
	for (int i = 0; i < *statesCount; i++) {
		commands[i] = new string[*statesCount + 1];
		for (int j = 0; j < *statesCount + 1; j++) {
			commands[i][j] = "";
		}
	}
	
	commands[0][1] = "loadmap";
	commands[1][1] = "loadmap";
	commands[1][2] = "validatemap";
	commands[2][3] = "addplayer";
	commands[3][3] = "addplayer";
	commands[3][4] = "assigncountries";
	commands[4][5] = "issueorder";
	commands[5][5] = "issueorder";
	commands[5][6] = "endissueorders";
	commands[6][6] = "execorder";
	commands[6][4] = "endexecorders";
	commands[6][7] = "win";
	commands[7][0] = "play";
	commands[7][8] = "end";
	
	*current = states[0];
}

bool GameEngine::transition(string command) {
	if (command == "") {
		cout << "Error: Command cannot be blank" << endl;
		return true;
	}
	
	// Get the index of the current orders
	int from = 0;
	for (int i = 0; i < *statesCount; i++) {
		if (*current == states[i]) {
			from = i;
		}
	}
	
	int to = -1;
	for (int i = 0; i < *statesCount + 1; i++) {
		if (command == commands[from][i]) {
			to = i;
		}
	}
	
	if (to == -1) {
		cout << "Error: Invalid state transition command" << endl;
		cout << "Cannot transition out of state \"" << *current;
		cout << "\" using command \"" << command << "\"" << endl;
	} else if (to == 8) {
		cout << "Ending program..." << endl;
		return false;
	} else {
		cout << "State transitioned from \"" << *current << "\" to \"" << states[to] << "\"" << endl;
		*current = states[to];
	}
	return true;
}