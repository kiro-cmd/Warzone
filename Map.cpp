#ifndef MAP_CPP
#define MAP_CPP

#include "Map.h"

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <cmath>
#include "ArrayLib.h"

using namespace std;

// - Territory functions -

Territory::Territory() {
	name = new string("No Name");
	xPosition = new double(0);
	yPosition = new double(0);
	continentName = new string("No Name");
	
	neighbourNames = new string[0];
	
	owner = new string("Nobody");
	armies = new int(0);
};

Territory::Territory(const Territory &rhs) {
	Territory& crhs = const_cast <Territory&>(rhs);
	
	name = new string(*crhs.name);
	xPosition = new double(*crhs.xPosition);
	yPosition = new double(*crhs.yPosition);
	continentName = new string(*crhs.continentName);
	
	for (int i = 0; i < crhs.getNeighbourNamesCount(); i++)
	{
		appendNeighbourName(string(crhs.neighbourNames[i]));
	}
	
	owner = new string(*crhs.owner);
	armies = new int(*crhs.armies);
}

// Destructor
Territory::~Territory() {
	delete name;
	delete xPosition;
	delete yPosition;
	delete continentName;
	delete neighbourNamesCount;
	delete [] neighbourNames;
	delete owner;
	delete armies;
};

// Custom assignent operator
Territory& Territory::operator=(const Territory &T) {
	if (this != &T)
	{
		name = new string(*T.name);
		xPosition = new double(*T.xPosition);
		yPosition = new double(*T.yPosition);
		continentName = new string(*T.continentName);
		
		neighbourNamesCount = new int(*T.neighbourNamesCount);
		neighbourNames = new string[*neighbourNamesCount];
		for (int i = 0; i < *T.neighbourNamesCount; i++){
			neighbourNames[i] = string(T.neighbourNames[i]);
		}
		owner = new string(*T.owner);
		armies = new int(*T.armies);
	}
	
	return *this;
}

// Stream inserion operator
ostream& operator<<(ostream &out, const Territory &T) {
	Territory& cT = const_cast <Territory&>(T);
	
	out << "- " << *cT.name << " at ";
	out << "(" << *cT.xPosition;
	out << ", " << *cT.yPosition << ") ";
	out << "is part of " << *cT.continentName << endl;
	out << "Neighbours: ";
	for (int i = 0; i < cT.getNeighbourNamesCount(); i++) {
		if (i != 0)
			out << ", ";
		out << cT.neighbourNames[i];
	}
	out << endl << "Owned by " << *T.owner;
	out << " with " << *T.armies << " armies" << endl;
	
	return out;
}

// Array functions
int Territory::getNeighbourNamesCount() {
	return *neighbourNamesCount;
}

void Territory::appendNeighbourName(string name) {
	push(neighbourNames, *neighbourNamesCount, name);
}

void Territory::clearNeighbourNames() {
	neighbourNames = new string[0];
	*neighbourNamesCount = 0;
}

// - Continent functions -

// Constructors
Continent::Continent() {
	name = new string("No Name");
	territoryNames = new string[0];
	armyBonus = new int(0);
};

Continent::Continent(const Continent &rhs) {
	Continent& crhs = const_cast <Continent&>(rhs);
	
	name = new string(*crhs.name);
	
	territoryNames = new string[crhs.getTerritoryNamesCount()];
	for (int i = 0; i < crhs.getTerritoryNamesCount(); i++) {
		appendTerritoryName(string(crhs.territoryNames[i]));
	}
	armyBonus = new int(*crhs.armyBonus);
}

// Destructor
Continent::~Continent() {
	delete name;
	delete territoryNamesCount;
	delete [] territoryNames;
	delete armyBonus;
};

// Stream Insertion Operator
ostream& operator<<(ostream &out, const Continent &C) {
	Continent& cC = const_cast <Continent&>(C);
	
	out << "- The continent of " << *cC.name << endl;
	out << "Territories: ";
	for (int i = 0; i < cC.getTerritoryNamesCount(); i++) {
		if (i != 0)
			out << ", ";
		out << cC.territoryNames[i];
	}
	out << endl <<"Conquering this continent grants a bonus of " << *cC.armyBonus << " armies per turn." << endl;
	
	return out;
}

// Custom Assignment Operator
Continent& Continent::operator=(const Continent &C) {
	if (this != &C) {
		name = new string(*C.name);
		
		territoryNamesCount = new int(*C.territoryNamesCount);
		territoryNames = new string[*territoryNamesCount];
		for (int i = 0; i < *territoryNamesCount; i++) {
			territoryNames[i] = string(C.territoryNames[i]);
		}
		armyBonus = new int(*C.armyBonus);
	}
	
	return *this;
}

// Other functions
int Continent::getTerritoryNamesCount() {
	return *territoryNamesCount;
}

void Continent::appendTerritoryName(string name) {
	push(territoryNames, *territoryNamesCount, name);
}

// - Map functions -

Map::Map() {
	author = new string("unknown author");
	image = new string("none");
	wrap = new bool(true);
	scroll = new string("horizontal");
	warn = new bool(true);
	continents = new Continent[0];
}

Map::Map(const Map &rhs){
	Map& crhs = const_cast <Map&>(rhs);
	
	author = new string(*crhs.author);
	image = new string(*crhs.image);
	wrap = new bool(*crhs.wrap);
	scroll = new string(*crhs.scroll);
	warn = new bool(*crhs.warn);
	
	continents = new Continent[0];
	int counter = 0;
	while (counter < crhs.getContinentsCount() || counter < crhs.getTerritoriesCount())
	{
		if (counter < crhs.getContinentsCount())
			appendContinent(Continent(rhs.continents[counter]));
		if (counter < crhs.getTerritoriesCount())
			appendTerritory(Territory(rhs.territories[counter]));
		counter++;
	}
}

// Destructor
Map::~Map() {
	delete author;
	delete image;
	delete wrap;
	delete scroll;
	delete warn;
	delete continentsCount;
	delete [] continents;
	delete territoriesCount;
	delete [] territories;
};

// Custom Assignment Operator
Map& Map::operator=(const Map &M) {
	if (this != &M)
	{
		author = new string(*M.author);
		image = new string(*M.image);
		wrap = new bool(*M.wrap);
		scroll = new string(*M.scroll);
		warn = new bool(*M.warn);
		
		continentsCount = new int(*M.continentsCount);
		continents = new Continent[*continentsCount];
		territoriesCount = new int(*M.territoriesCount);
		territories = new Territory[*territoriesCount];
		int counter = 0;
		while (counter < *continentsCount || counter < *territoriesCount)
		{
			if (counter < *continentsCount)
				continents[counter] = Continent(M.continents[counter]);
			if (counter < *territoriesCount)
				territories[counter] = Territory(M.territories[counter]);
			counter++;
		}
	}
	return *this;
}

// Stream insertion operator
ostream& operator<<(ostream &out, const Map &M) {
	Map& cM = const_cast <Map&>(M);
	
	out << "This map was made by " << *cM.author << endl;
	out << "This map uses the following image file: " << *cM.image << endl;
	if (*cM.wrap)
		out << "This map wraps, ";
	else
		out << "This map does not wrap, ";
	out << "has " << *cM.scroll << " scrolling, and ";
	if (*cM.warn)
		out << "warns.";
	else
		out << "does not warn.";
	
	out << endl << endl << "Continents:" << endl;
	for (int i = 0; i < cM.getContinentsCount(); i++) {
		out << cM.continents[i];
	}
	out << endl << "Territories:" << endl;
	for (int i = 0; i < cM.getTerritoriesCount(); i++) {
		out << cM.territories[i];
	}
	
	return out;
}

// Array functions
Territory Map::getTerritory(string name) {
	for (int i = 0; i < getTerritoriesCount(); i++) {
		if (*territories[i].name == name) {
			return territories[i];
			break;
		}
	}
	
	Territory dummy;
	*dummy.name = "dummy";
	return dummy;
}

Continent Map::getContinent(string name) {
	for (int i = 0; i < getContinentsCount(); i++) {
		if (*continents[i].name == name) {
			return continents[i];
			break;
		}
	}
	
	Continent dummy;
	*dummy.name = "dummy";
	return dummy;
}

int Map::getContinentsCount() {
	return *continentsCount;
}

void Map::appendContinent(Continent c) {
	push(continents, *continentsCount, c);
}

int Map::getTerritoriesCount() {
	return *territoriesCount;
}

void Map::appendTerritory(Territory t) {
	push(territories, *territoriesCount, t);
}

// This returns true if the Map is in a valid format.
bool Map::validate() {
	// Map must have at least 1 territory.
	if (*territoriesCount == 0) {
		return false;
	}
	
	bool valid = true;
	
	string* territoryOdyssey = new string[1];
	int odysseyCount = 1;
	territoryOdyssey[0] = string(*territories[0].name);
	string* continentOdyssey = new string[0];
	int cOdysseyCount = 0;
	string* territoriesToCheck = new string[1];
	int checkCount = 1;
	territoriesToCheck[0] = string(*territories[0].name);
	
	while (checkCount != 0) {
		for (int i = checkCount - 1; i >= 0; i--) {
			Territory current = getTerritory(pop(territoriesToCheck, checkCount));
			for (int j = 0; j < current.getNeighbourNamesCount(); j++) {
				Territory currentNeighbour = getTerritory(current.neighbourNames[j]);
				if (isUniqueElement(territoryOdyssey, odysseyCount, *currentNeighbour.name)) {
					push(territoryOdyssey, odysseyCount, string(*currentNeighbour.name));
					push(territoriesToCheck, checkCount, string(*currentNeighbour.name));
				}
				if (isUniqueElement(continentOdyssey, cOdysseyCount, *currentNeighbour.continentName)) {
					push(continentOdyssey, cOdysseyCount, string(*currentNeighbour.continentName));
				}
			}
		}
	}
	
	// - Check if the map is a connected graph
	//   - This means that it must be possible to go
	//     from any territory to any other territory
	//     by moving to a territory's neighbouring
	//     territory repeatedly.
	//   - This will pass the test if the length of
	//     territoryOdessey matches the number of
	//     territories.
	if (odysseyCount != *territoriesCount) {
		cout << "Not all territories have been passed through!" << endl;
		cout << "Full list of territories: ";
		for (int i = 0; i < *territoriesCount; i++) {
			if (i != 0) { cout << ", "; }
			cout << *territories[i].name;
		}
		cout << endl << "Territories passed through: ";
		cout << arrayToString(territoryOdyssey, odysseyCount) << endl;
		cout << endl;
		valid = false;
	}
	
	// - Check continents are a connected subgraph
	//   - Meaning that you can visit every
	//     continent using the above logic.
	if (cOdysseyCount != *continentsCount) {
		cout << "Not all continents have been passed through!" << endl;
		cout << "Full list of continents: ";
		for (int i = 0; i < *continentsCount; i++) {
			if (i != 0) { cout << ", "; }
			cout << *continents[i].name;
		}
		cout << "Continents passed through: ";
		cout << arrayToString(continentOdyssey, cOdysseyCount) << endl;
		valid = false;
	}
	
	// The third condition is to ensure that every
	//   territory belongs to only one continent.
	// However, this is already guaranteed given the
	//   way the Territory properties are organized
	//   and generated.
	
	delete [] territoryOdyssey;
	delete [] continentOdyssey;
	delete [] territoriesToCheck;
	
	return valid; 
}

// - MapLoader functions -

// -- Miscellaneous tools used in the map file reading function --
string MapLoader::RemoveStringEnds(string oldStr) {
	string newStr = "";
	
	for (int i = 1; i < oldStr.length() - 1; i++) {
		char c = oldStr[i];
		newStr = newStr + c;
	}
	
	return newStr;
}

// -- VALIDITY CHECKERS --
bool MapLoader::isStringANumber(string s, bool negative) {
	// This returns true if s is a number that...
	// - is positive or negative (only positive if negative is false)
	// - has any number of decimal digits
	// - has one or zero floating points anywhere
	bool valid = true;
	int fPoints = 0;
	
	for (int i = 0; i < s.length(); i++)
	{
		if (!(s[i] == '-' && i == 0 && negative)
			&& !(s[i] >= '0' && s[i] <= '9')
			&& !(s[i] == '.' && fPoints < 1))
		{
			valid = false;
			break;
		}
	}
	
	return valid;
}

bool MapLoader::isUniqueContinent(Continent* array, int aSize, Continent elem) {
	string* names = new string[aSize];
	for (int i = 0; i < aSize; i++) {
		names[i] = *array[i].name;
		}
	return isUniqueElement(names, aSize, *elem.name);
}

bool MapLoader::isUniqueTerritory(Territory* array, int aSize, Territory elem) {
	string* names = new string[aSize];
	for (int i = 0; i < aSize; i++) {
		names[i] = *array[i].name;
		}
	return isUniqueElement(names, aSize, *elem.name);
}

Map MapLoader::testLoadMap(string directory, string filename) {
	Map importedMap;
	// TO-DO: adjust code to account for other required variables other than "image"
	importedMap.image = new string("");
	string classToDescribe = "";
	string s;
	
	ifstream MyReadFile(directory + "/" + filename);
	string line;
	
	bool error = false;
	
	Territory t;
	
	while (getline (MyReadFile, line)) {
		if (line[0] == '[' && line[line.length() - 1] == ']') {
			classToDescribe = RemoveStringEnds(line);
			continue;
		}
		
		if (classToDescribe == "Map") {
			string property = "";
			string value = "";
			bool readingValue = false;
			
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == '=')
					readingValue = true;
				else {
					char c = line[i];
					if (readingValue)
						value = value + c;
					else
						property = property + c;
				}
			}
			
			if (property == "author") importedMap.author = new string(value);
			else if (property == "image") {
				importedMap.image = new string(value);
				
				// TO-DO: Test if only .bmp formats are accepted?
				regex re (".*\\.bmp$");
				if (!regex_match(*importedMap.image, re)) {
					cout << "Error! " << *importedMap.image << " must have a .bmp file extension!";
					error = true;
					break;
				}
				
				// Testing to see if the file exists
				ifstream test;
				test.open(directory + "/" + *importedMap.image);
				bool fileExists = test.is_open();
				test.close();
				if (!fileExists) {
					cout << "Error! " << *importedMap.image << " does not exist!";
					error = true;
					break;
				}
			}
			else if (property == "wrap") *importedMap.wrap = (value == "yes") ? true : false;
			else if (property == "scroll") importedMap.scroll = new string(value);
			else if (property == "warn") *importedMap.warn = (value == "yes") ? true : false;
		}
		else if (classToDescribe == "Continents") {
			if (*importedMap.image == "") {
				cout << "Error: Either Continents are being defined before the Map, or the Map was not properly defined." << endl;
				error = true;
				break;
			}
			
			string name = "";
			string bonus = "";
			bool readingName = true;
			
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == '=')
					readingName = false;
				else
				{
					char c = line[i];
					if (readingName)
					{
						name = name + c;
					}
					else
					{
						bonus = bonus + c;
					}
				}
			}
				
			if (name != "") {
				Continent newContinent;
				newContinent.name = new string(name);
				if (!isStringANumber(bonus, false)) {
					cout << "Error! " << *newContinent.name << "'s bonus value in file is not a number!" << endl;
					error = true;
					break;
				}
				newContinent.armyBonus = new int(stoi(bonus));
				if (!isUniqueContinent(importedMap.continents, importedMap.getContinentsCount(), newContinent)) {
					cout << "Error! " << *newContinent.name << " is not a unique Continent name!" << endl;
					error = true;
					break;
				}
				importedMap.appendContinent(newContinent);
			}
		}
		else if (classToDescribe == "Territories") {
			if (*importedMap.image == "") {
				cout << "Error: Either Continents are being defined before the Map, or the Map was not properly defined." << endl;
				error = true;
				break;
			}
			
			if (importedMap.getContinentsCount() == 0) {
				cout << "Error: Either Territories are being defined before Continents, or Continents were not properly defined." << endl;
				error = true;
				break;
			}
			
			int commas = 0;
			string property = "";
			
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ',') {
					if (commas == 0) {
						t.name = new string(property);
					}
					else if (commas == 1) {
						if (!isStringANumber(property, true)) {
							cout << "Error! " << *t.name << " x-position value in file is not a number!" << endl;
							error = true;
						}
						
						t.xPosition = new double(stod(property));
					}
					else if (commas == 2) {
						if (!isStringANumber(property, true)) {
							cout << "Error! " << *t.name << " y-position value in file is not a number!" << endl;
							error = true;
						}
						t.yPosition = new double(stod(property));
					}
					else if (commas == 3) {
						t.continentName = new string(property);
						
						// Insert the territory name in its continent
						for (int j = 0; j < importedMap.getContinentsCount(); j++) {
							Continent current = importedMap.continents[j];
							if (*current.name == *t.continentName) {
								if (!isUniqueElement(current.territoryNames, current.getTerritoryNamesCount(), *t.name)) {
									cout << "Error! " << *current.name << "'s territories must be unique!" << endl;
									error = true;
								}
								
								importedMap.continents[j].appendTerritoryName(*t.name);
								break;
							}
							else {
								continue;
							}
						}
					}
					else {
						if (property == *t.name) {
							cout << "Error! " << *t.name << " is neighbouring itself!" << endl;
							error = true;
						}
						
						// One of the test maps had duplicate entries. Just ignore any duplicates.
						if (isUniqueElement(t.neighbourNames, t.getNeighbourNamesCount(), property)) {
							t.appendNeighbourName(property);
						}
					}
					
					property = "";
					commas++;
				}
				else {
					char c = line[i];
					
					property = property + c;
				}
					
				if (i == line.length() - 1) {
					if (isUniqueElement(t.neighbourNames, t.getNeighbourNamesCount(), property)) {
						t.appendNeighbourName(property);
					}
					
					if (!isUniqueTerritory(importedMap.territories, importedMap.getTerritoriesCount(), t)) {
						cout << "Error! " << *t.name << " is not a unique Territory name!" << endl;
						error = true;
					}
					
					importedMap.appendTerritory(Territory(t));
					t.clearNeighbourNames();
				}
			}
			
			if (commas < 1 && line.length() != 0) {
				cout << "Error: No x-coordinate listed for " << *t.name << " (" << commas << " commas)" << endl;
				error = true;
			}
			else if (commas < 2 && line.length() != 0) {
				cout << "Error: No y-coordinate neighbours listed for " << *t.name << " (" << commas << " commas)" << endl;
				error = true;
			}
			else if (commas < 3 && line.length() != 0) {
				cout << "Error: No continent listed for " << *t.name << " (" << commas << " commas)" << endl;
				error = true;
			}
			else if (commas < 4 && line.length() != 0) {
				cout << "Error: No territory neighbours listed for " << *t.name << " (" << commas << " commas)" << endl;
				error = true;
			}
		}
		
		if (classToDescribe == "" && line.length() != 0) {
			cout << "Error: properties are listed before a class is described!" << endl;
			error = true;
		}
	}
	
	MyReadFile.close();
	
	if (error) {
		cout << "An error has occured!";
		return Map();
	}
	
	// cout << "- - -\n\n";
	
	// cout << importedMap;
	return importedMap;
}

#endif