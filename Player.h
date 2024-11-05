#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "Map.cpp"
#include "Card.cpp"
#include "Order.cpp"

using namespace std;

class Player {
	
	int* territoriesCount = new int(0);
	int* handCount = new int(0);
	int* orderListCount = new int(0);
	
	public:
		string name;                     // Player's name as a regular string
		string* territories;             // Dynamic array of owned string names
		string* hand;                    // Dynamic array of card types
		string* orderList;               // Dynamic array of order types
		
		// Constructors
		Player();
		
		// Assume that the arrays were made to populaate this class'
		//   attributes, and can simply be pointed to.
		Player(string name, string* tList, string* cList, string* oList);
		Player(const Player& rhs);

		// Assignment operator (Deep Copy)
		Player& operator=(const Player& rhs);
		
		// Destructor
		~Player();

		// Methods to return certain player properties
		
		// This deep copies the entire list for now
		string* territoriesToAttack();
		int ttaCount();
		
		string* territoriesToDefend();
		int ttdCount();

		void issueOrder(string order);

		string* getOrderList();
		
		// array methods
		int getTerritoriesCount();
		
		void appendTerritoryName(string t);
		
		int getHandCount();
		
		void appendToHand(string c);
		
		int getOrderListCount();
		
		void appendOrder(string o);
		
		friend ostream& operator<<(ostream& out, const Player& P);
};

class PlayerDriver {
	public:
		static Player* makeThreePlayers() {
			Player p1 = Player();
			p1.name = "Alice";
			p1.appendTerritoryName("The North");
			p1.appendTerritoryName("The South-West");
			p1.appendToHand("4 of hearts");
			p1.appendToHand("7 of clubs");
			p1.appendOrder("Attack");
			p1.appendOrder("Defend");
			
			Player p2 = Player();
			p2.name = "Bob";
			p2.appendTerritoryName("The North-East");
			p2.appendTerritoryName("The South-East");
			p2.appendToHand("Jack of spadess");
			p2.appendToHand("10 of spadess");
			p2.appendOrder("Attack");
			p2.appendOrder("Defend");
			p2.appendOrder("Defend");
			
			Player p3 = Player();
			p3.name = "Charlie";
			p3.appendTerritoryName("The North-West");
			p3.appendTerritoryName("The South");
			p3.appendToHand("2 of clubs");
			p3.appendToHand("6 of diamonds");
			p3.appendOrder("Defend");
			p3.appendOrder("Attack");
			p3.appendOrder("Defend");
			
			Player* pList = new Player[3];
			pList[0] = p1;
			pList[1] = p2;
			pList[2] = p3;
			
			return pList;
		};
		
		// Assumes there are 3 players in the list
		static string testPlayers(Player* pList) {
			string toReturn = "";
			toReturn = toReturn + "Testing player actions...\n";
			
			toReturn = toReturn + "\nGetting territories to attack from p1...\n- ";
			string* attackT = pList[0].territoriesToAttack();
			int atCount = pList[0].ttaCount();
			for (int i = 0; i < atCount; i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + attackT[i];
			}
			delete [] attackT;
			
			toReturn = toReturn + "\n\nGetting territories to defend from p2...\n- ";
			string* defendT = pList[1].territoriesToDefend();
			int dtCount = pList[1].ttdCount();
			for (int i = 0; i < dtCount; i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + defendT[i];
			}
			delete [] defendT;
			
			toReturn = toReturn + "\n\np3's current orders are...\n- ";
			for (int i = 0; i < pList[2].getOrderListCount(); i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + pList[2].orderList[i];
			}
			toReturn = toReturn + "\nissuing an extra \"Attack\" order to p3...";
			pList[2].issueOrder("Attack");
			toReturn = toReturn + "\np3's current orders are...\n- ";
			for (int i = 0; i < pList[2].getOrderListCount(); i++) {
				if (i != 0) { toReturn = toReturn + ", "; }
				toReturn = toReturn + pList[2].orderList[i];
			}
			
			return toReturn;
		}
};

#endif // PLAYER_H