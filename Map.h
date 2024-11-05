#ifndef MAP_H
#define MAP_H

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>
#include "ArrayLib.h"

using namespace std;

// Represents an in-game territory.
// Contains the territory's name, map corrdinates,
//   continent name, list of neighbouring territories,
//   territory owner and number of armies.
// NOTE: Continent name may be unnecessary.
// NOTE: The owner and armies attributes are currently
//       unused.
// NOTE: To avoid redundant data, only the names of each
//       neighbouring territory are stored here. To
//       retrieve the entire territory, a function from
//       this territory's map must be called
class Territory
{
	int* neighbourNamesCount = new int(0);
		
	public:
		string* name;
		double* xPosition;
		double* yPosition;
		string* continentName;
		string* neighbourNames;
		string* owner;
		int* armies;
		
		// Constructors
		Territory();;
		Territory(const Territory &rhs);
		
		// Destructor
		~Territory();
		
		// Custom assignent operator
		Territory& operator=(const Territory &T);
		
		// Stream inserion operator
		friend ostream& operator<<(ostream &out, const Territory &T);
		
		// Array functions
		int getNeighbourNamesCount();
		void appendNeighbourName(string name);
		void clearNeighbourNames();
};

// Represents an in-game Continent
// Each continent has a name, a list of territories,
//   and an army generation bonus when a player has
//   conquered all of its territories.
// NOTE: To avoid redundant data, only the names of each
//       territory are stored here. To retrieve the entire
//       territory, a function from this continent's Map
//       must be called.
class Continent
{
	int* territoryNamesCount = new int(0);
	
	public:
		string* name;
		string* territoryNames;
		int* armyBonus;
		
		// Constructors
		Continent();
		Continent(const Continent &rhs);
		
		// Destructor
		~Continent();
		
		// Stream Insertion Operator
		friend ostream& operator<<(ostream &out, const Continent &C);
		
		// Custom Assignment Operator
		Continent& operator=(const Continent &C);
		
		// Other functions
		int getTerritoryNamesCount();
		
		void appendTerritoryName(string name);
};

// Represents the map where the game takes place.
// Contains metadata, as well as a list of continents
//   and territories.
// This class is also responsible for retrieving territories
//   for the Continent and Territory classes.
class Map
{
	int* continentsCount = new int(0);
	int* territoriesCount = new int(0);
	
	public:
		string* author;
		string* image;
		bool* wrap;
		string* scroll;
		bool* warn;
		Continent* continents;
		Territory* territories;
	
		// Get the territory object whose name matches the string
		
		// Constructor
		Map();
		Map(const Map &rhs);
		
		// Destructor
		~Map();
		
		// Custom Assignment Operator
		Map& operator=(const Map &M);
		
		// Stream insertion operator
		friend ostream& operator<<(ostream &out, const Map &M);
		
		// Array functions
		Territory getTerritory(string name);
		Continent getContinent(string name);
		
		int getContinentsCount();
		void appendContinent(Continent c);
		
		int getTerritoriesCount();;
		void appendTerritory(Territory t);
		
		bool validate();
};

// Static class whose only purpose is to make a
//   Map object from a .map file.
// NOTE: This currently does not return a map object,
//       only printing it to the console.
class MapLoader {
	static string RemoveStringEnds(string oldStr);
	
	static bool isStringANumber(string s, bool negative);
	static bool isUniqueContinent(Continent* array, int aSize, Continent elem);
	static bool isUniqueTerritory(Territory* array, int aSize, Territory elem);
	
	public:
		static Map testLoadMap(string directory, string filename);
};

#endif