#include <string>
#include <iostream>
#include "Map.cpp"
#include "Player.cpp"
#include "Order.cpp"
#include "Card.cpp"
#include "GameEngine.cpp"
#include "ArrayLib.h"

using namespace std;

int main() {
	/* testing Game Engine and Command Processor
	GameEngine ge;
	*ge.running = true;
	
	while(*ge.running) {
		ge.command();
	}
	*/
	
	// reading commands from a file
	FileCommandProcessorAdapter fcpa;
	fcpa.readFromFile("fcpa_commands.txt");
	
	return 0;
}