#include <string>
#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Order.h"
#include "Card.h"
#include "GameEngine.h"

using namespace std;

int main() {
	cout << "Hello World!" << endl;
	
	Map m = MapLoader::testLoadMap("mapSourceFiles", "Earth.map");
	// cout << m << endl;
	// cout << boolalpha << m.validate() << endl;
	
	return 0;
}