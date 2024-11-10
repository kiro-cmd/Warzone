#ifndef GAMEENGINE_CPP
#define GAMEENGINE_CPP

#include "GameEngine.h"

#include <iostream>
#include <string>
#include "CommandProcessor.cpp"

using namespace std;

GameEngine::GameEngine() {
	statesCount = new int(8);
	
	states = new string[*statesCount];
	states[0] = "start";
	states[1] = "maploaded";
	states[2] = "mapvalidated";
	states[3] = "playersadded";
	states[4] = "assignreinforcement";
	states[5] = "issueorders";
	states[6] = "executeorders";
	states[7] = "win";
	
	canTrans = new bool*[*statesCount];
	for (int i = 0; i < *statesCount; i++) {
		canTrans[i] = new bool[*statesCount + 1];
		for (int j = 0; j < *statesCount + 1; j++) {
			canTrans[i][j] = "";
		}
	}
	
	canTrans[0][1] = true;
	canTrans[1][1] = true;
	canTrans[1][2] = true;
	canTrans[2][3] = true;
	canTrans[3][3] = true;
	canTrans[3][4] = true;
	canTrans[4][5] = true;
	canTrans[5][5] = true;
	canTrans[5][6] = true;
	canTrans[6][6] = true;
	canTrans[6][4] = true;
	canTrans[6][7] = true;
	canTrans[7][0] = true;
	canTrans[7][8] = true;
	
	*current = states[0];
}

GameEngine::~GameEngine() {
	delete running;
	delete current;
	delete [] states;
	for (int i = 0; i < *statesCount + 1; i++) {
		delete [] canTrans[i];
	}
	delete [] canTrans;
	delete statesCount;
	delete cp;
}

// prompts the user to enter a command.
// the Command Processor class handles (most of) the processing
void GameEngine::command() {
	cp->getCommand(*current);
	Command c = cp->popCommand();
	string effect = string(*c.effect);
	*running = transition(effect);
}

int GameEngine::getStateIndex(string state) {
	if (state == "end") {
		return *statesCount;
	}
	
	for (int i = 0; i < *statesCount; i++) {
		if (states[i] == state) {
			return i;
		}
	}
	
	return -1;
}

// returns false if the game engine is exited
// returns true otherwise.
bool GameEngine::transition(string toState) {
	if (toState == "") {
		cout << "Error: State cannot be blank" << endl;
		return true;
	}
	
	// Get the index of the current state
	int from = getStateIndex(*current);
	int to = getStateIndex(toState);
	
	if (!canTrans[from][to]) {
		to = -1;
	}
	
	if (to == -1) {
		cout << "Error: Invalid state transition command" << endl;
		cout << "Cannot transition from state \"" << *current;
		cout << "\" to state \"" << toState << "\"" << endl;
	} else if (to == *statesCount) {
		cout << "Ending program..." << endl;
		return false;
	} else {
		cout << "State transitioned from \"" << *current << "\" to \"" << states[to] << "\"" << endl;
		*current = states[to];
	}
	return true;
}

#endif