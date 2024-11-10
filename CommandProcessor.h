#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>
#include <iostream>
#include "ArrayLib.h"

using namespace std;

class Command {
	public:
		string* input = new string("");
		string* effect = new string("");
		
		Command();
		Command(string i);
		Command(const Command &rhs);
		
		Command operator=(Command const& rhs);

		~Command();
		
		void saveEffect(string e);
};

class CommandProcessor {
	private:
		int* commandsCount = new int(0);
		
		string readCommand();
		void validate(Command &command, string currentState);
	public:
		Command* commands = new Command[0];
		
		CommandProcessor();
		
		~CommandProcessor();
		
		void getCommand(string currentState);
		void saveCommand(string input, string currentState);
		
		int getCommandsCount();
		void appendCommand(Command &c);
		string checkCommand(string input, string commandCheck, string currentState, string* validFrom, int validCount, string to);
		Command popCommand();
};

class FileCommandProcessorAdapter {
	public:
		static void readFromFile(string filename);
};

#endif