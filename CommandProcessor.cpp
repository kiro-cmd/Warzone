#ifndef COMMANDPROCESSOR_CPP
#define COMMANDPROCESSOR_CPP

#include "CommandProcessor.h"

#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "ArrayLib.h"

using namespace std;

// - Command methods -

Command::Command() {};
// If this contructor is called, assume the input is valid.
Command::Command(string i) {
	*input = i;
}
Command::Command(const Command &rhs) {
	input = new string(*rhs.input);
		effect = new string(*rhs.effect);
}

Command Command::operator=(Command const& rhs) {
	if (this != &rhs) {
		input = new string(*rhs.input);
		effect = new string(*rhs.effect);
	}
	return *this;
}

Command::~Command() {
	delete input;
	delete effect;
}

void Command::saveEffect(string e) {
	*effect = e;
}

// - Command Processor methods -

CommandProcessor::CommandProcessor() {}

CommandProcessor::~CommandProcessor() {
	delete commandsCount;
	delete [] commands;
}

void CommandProcessor::getCommand(string currentState) {
	cout << "Enter command: ";
	string input = readCommand();
	saveCommand(input, currentState);
}

string CommandProcessor::readCommand() {
	string input;
	cin >> input;
	return input;
}

void CommandProcessor::saveCommand(string input, string currentState) {
	Command c(input);
	validate(c, currentState);
	appendCommand(c);
}

string CommandProcessor::checkCommand(string input, string commandCheck, string currentState, string* validFrom, int validCount, string to) {
	// Does the current state match one of the valid "from" states?
	bool validCommand = false;
	for (int i = 0; i < validCount; i++) {
		if (currentState == validFrom[i]) {
			validCommand = true;
			break;
		}
	}
	
	string effect = "";
	
	if (regex_match(input, regex(commandCheck))) {
		if (validCommand) {
			effect = to;
		}
	}
	
	return effect;
}

// TO-DO: save command arguments
void CommandProcessor::validate(Command &command, string currentState) {
	string effect = "Error: Unrecognized command";
	string test;
	string* validFrom;
	
	// regex expession ( [^ ]+)?$ means...
	// - either nothing, or...
	// - a space followed by an argument of length 1 or more.
	
	validFrom = new string[2];
	validFrom[0] = "start";
	validFrom[1] = "maploaded";
	test = checkCommand(*command.input, "^loadmap( [^ ]+)?$", currentState, validFrom, 2, "maploaded");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "maploaded";
	test = checkCommand(*command.input, "validatemap", currentState, validFrom, 1, "mapvalidated");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[2];
	validFrom[0] = "mapvalidated";
	validFrom[1] = "playersadded";
	test = checkCommand(*command.input, "^addplayer( [^ ]+)?$", currentState, validFrom, 2, "playersadded");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "playersadded";
	test = checkCommand(*command.input, "gamestart", currentState, validFrom, 1, "assignreinforcement");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[2];
	validFrom[0] = "assignreinforcement";
	validFrom[1] = "issueorders";
	test = checkCommand(*command.input, "issueorder", currentState, validFrom, 2, "issueorders");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "issueorders";
	test = checkCommand(*command.input, "issueordersend", currentState, validFrom, 1, "executeorders");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "executeorders";
	test = checkCommand(*command.input, "execorder", currentState, validFrom, 1, "executeorders");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "executeorders";
	test = checkCommand(*command.input, "endexecorders", currentState, validFrom, 1, "assignreinforcement");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "executeorders";
	test = checkCommand(*command.input, "win", currentState, validFrom, 1, "win");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "win";
	test = checkCommand(*command.input, "replay", currentState, validFrom, 1, "start");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	validFrom = new string[1];
	validFrom[0] = "win";
	test = checkCommand(*command.input, "quit", currentState, validFrom, 1, "end");
	if (test != "") { effect = string(test); }
	delete [] validFrom;
	
	command.saveEffect(effect);
}

int CommandProcessor::getCommandsCount() {
	return *commandsCount;
}

void CommandProcessor::appendCommand(Command &c) {
	push(commands, *commandsCount, c);
}

Command CommandProcessor::popCommand() {
	return pop(commands, *commandsCount);
}

// - The FileCommandProcessorAdapter -

void FileCommandProcessorAdapter::readFromFile(string filename) {
	string directory = "assets";
	
	ifstream MyReadFile(directory + "/" + filename);
	string line = "";
	
	cout << "Placeholder: printing lines for now." << endl;
	while(getline(MyReadFile, line)) {
		cout << line << endl;
	}
}

#endif