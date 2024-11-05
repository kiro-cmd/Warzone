#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"

#include <string>
#include <iostream>
#include "Map.cpp"
#include "Card.cpp"
#include "Order.cpp"
#include "ArrayLib.h"

using namespace std;

Player::Player() {
	name = "Unnamed Player";
	territories = new string[0];      // Initialize empty array for territories
	hand = new string[0];             // Initialize empty array for cards
	orderList = new string[0];        // Initialize empty array for orders
}

Player::Player(string name, string* tList, string* cList, string* oList) {
	name = name; 
	territories = tList;
	hand = cList;
	orderList = oList;
}

Player::Player(const Player& rhs) {
	Player& crhs = const_cast <Player&>(rhs);
	
	name = string(crhs.name);

	// Deep copies of all of the lists' elements
	territories = new string[crhs.getTerritoriesCount()];
	for (int i = 0; i < crhs.getTerritoriesCount(); i++) {
		appendTerritoryName(string(crhs.territories[i]));  // Deep copy of each string
	}

	hand = new string[crhs.getHandCount()];
	for (int i = 0; i < crhs.getHandCount(); i++) {
		appendToHand(string(crhs.hand[i]));  // Deep copy of each string
	}

	orderList = new string[crhs.getOrderListCount()];
	for (int i = 0; i < crhs.getOrderListCount(); i++) {
		appendOrder(string(crhs.orderList[i]));  // Deep copy of each string
	}
}

Player& Player::operator=(const Player& rhs) {
	if (this != &rhs) {
		Player& crhs = const_cast <Player&>(rhs);
		
		name = string(crhs.name);

		// Deep copies of all of the lists' elements
		territories = new string[crhs.getTerritoriesCount()];
		for (int i = 0; i < crhs.getTerritoriesCount(); i++) {
			appendTerritoryName(string(crhs.territories[i]));  // Deep copy of each string
		}

		hand = new string[crhs.getHandCount()];
		for (int i = 0; i < crhs.getHandCount(); i++) {
			appendToHand(string(crhs.hand[i]));  // Deep copy of each string
		}

		orderList = new string[crhs.getOrderListCount()];
		for (int i = 0; i < crhs.getOrderListCount(); i++) {
			appendOrder(string(crhs.orderList[i]));  // Deep copy of each string
		}
	}
	
	return *this;
}

Player::~Player() {
	delete territoriesCount;
	delete [] territories;
	delete handCount;
	delete [] hand;
	delete orderListCount;
	delete [] orderList;
}

// methods to return certain properties

string* Player::territoriesToAttack() {
	int len = ttaCount();
	string* atList = new string[len];
	for (int i = 0; i < len; i++) {
		atList[i] = string(territories[i]);
	}
	return atList;
}
int Player::ttaCount() {
	return *territoriesCount;  // Placeholder, returns the list length
}

string* Player::territoriesToDefend() {
	int len = ttdCount();
	string* dtList = new string[len];
	for (int i = 0; i < len; i++) {
		dtList[i] = string(territories[i]);
	}
	return dtList;
}

int Player::ttdCount() {
	return *territoriesCount;  // Placeholder, returns the list length
}

void Player::issueOrder(string order) {
	appendOrder(order);  // Adds an order to the list
}

string* Player::getOrderList() {
	return orderList;  // Returns order list
}

// Array Methods
int Player::getTerritoriesCount() {
	return *territoriesCount;
}

void Player::appendTerritoryName(string t) {
	push(territories, *territoriesCount, t);
}

int Player::getHandCount() {
	return *handCount;
}

void Player::appendToHand(string c) {
	push(hand, *handCount, c);
}

int Player::getOrderListCount() {
	return *orderListCount;
}

void Player::appendOrder(string o) {
	push(orderList, *orderListCount, o);
}

ostream& operator<<(ostream& out, const Player& P) {
	Player& cP = const_cast <Player&>(P);
	
	out << "Player Name: " << cP.name << endl;

	out << "Territories owned: ";
	for (int i = 0; i < cP.getTerritoriesCount(); i++) {
		if (i != 0) { out << ", "; }
		out << cP.territories[i];
	}
	out << endl;

	out << "Orders: ";
	for (int i = 0; i < cP.getOrderListCount(); i++) {
		if (i != 0) { out << ", "; }
		out << cP.orderList[i];  // Get the order type (they will likely be stored by type(?))
	}
	out << endl;

	// TO-DO: Find out what cards are and what they do
	out << "Cards: ";
	for (int i = 0; i < cP.getHandCount(); i++) {
		if (i != 0) { out << ", "; }
		out << cP.hand[i];  // Get the card type (they will likely be stored by type(?))
	}
	out << endl;

	return out;
}

#endif