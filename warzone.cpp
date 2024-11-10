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
	// testing Game Engine and Commnd Processor
	GameEngine ge;
	*ge.running = true;
	
	while(*ge.running) {
		ge.command();
	}
	
	return 0;
}