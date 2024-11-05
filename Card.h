#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <random>
#include "ArrayLib.h"

using namespace std;

class Card {
	private:
		int* cardType; // Stores the type of the card as a pointer Type
	public:
		// blank type card exists for error checking purposes
		enum cardType {
			blank,
			bomb,
			reinforcement,
			blockade,
			airlift,
			diplomacy
		};

		Card();
		Card(int cardType);
		// clone method
		Card(const Card& other);

		~Card();
		
		string getCardTypeName() const;
		
		Card& operator=(const Card& other);

		friend ostream& operator<<(ostream& out, const Card& card);

		int getCardType() const;
		
		void play();
};

class Deck {
	private:
		int* mainDeckCount = new int(0);
		Card* mainDeck = new Card[0];
		
	public:
		Deck();
		Deck(const Deck& rhs);
		
		~Deck();

		Deck& operator=(const Deck& rhs);
		
		int getDeckSize();
		
		void removeCard(int index);

		Card draw();

		void addCard(Card card);
		
		friend ostream& operator<<(ostream& out, const Deck& D);
};

class Hand {
	private:
		int* cardsCount = new int(0);
		Card* handCards = new Card[0];  // Cards in the hand
		Deck& sharedDeck; 
		
	public:
		Hand(Deck& deck);
		Hand(const Hand& rhs);
		Hand& operator=(const Hand& rhs);

		~Hand();

		// Draws a card from the shared Deck and adds it to the hand
		void drawCard();

		void playCard(int index);

		void showHand() const;

		friend ostream& operator<<(ostream& out, const Hand& hand);
};

#endif // CARD_H