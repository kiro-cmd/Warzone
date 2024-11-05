#ifndef CARD_CPP
#define CARD_CPP

#include "Card.h"

#include <iostream>
#include <random>
#include "ArrayLib.h"

// - Card Methods -

Card::Card() {
	cardType = new int(0);
}

Card::Card(int ct) {
	cardType = new int(ct);
}

Card::Card(const Card& other) {
	cardType = new int(*(other.cardType));
}

string Card::getCardTypeName() const {
	switch (*cardType) {
	case blank:
		return "Blank";
	case bomb:
		return "Bomb";
	case reinforcement:
		return "Reinforcement";
	case blockade:
		return "Blockade";
	case airlift:
		return "Airlift";
	case diplomacy:
		return "Diplomacy";
	default:
		return "Unknown";
	}
}

Card::~Card() {
	delete cardType;
}

Card& Card::operator=(const Card& other) {
	if (this != &other) {
		if (cardType != nullptr) {
			delete cardType;
		}
		cardType = new int(*other.cardType);
	}
	return *this;
}

ostream& operator<<(ostream& out, const Card& C) {
	Card& cC = const_cast <Card&>(C);
	
	out << "Card type: " << cC.getCardTypeName();
	return out;
}

int Card::getCardType() const {
	return *cardType;
}

void Card::play() {
	cout << "Playing card of type: " << getCardTypeName() << endl;
}

// - Deck functions -

Deck::Deck() {
	for (int i = 0; i < 5; ++i) {
		push(mainDeck, *mainDeckCount, Card(Card::bomb));
		push(mainDeck, *mainDeckCount, Card(Card::reinforcement));
		push(mainDeck, *mainDeckCount, Card(Card::blockade));
		push(mainDeck, *mainDeckCount, Card(Card::airlift));
		push(mainDeck, *mainDeckCount, Card(Card::diplomacy));
	}
	shuffle(mainDeck, *mainDeckCount);
}

Deck::Deck(const Deck& rhs) {
	mainDeckCount = new int(*rhs.mainDeckCount);
	mainDeck = new Card[*mainDeckCount];
	for (int i = 0; i < *mainDeckCount; i++) {
		mainDeck[i] = Card(rhs.mainDeck[i]);
	}
}

Deck::~Deck() {
	delete mainDeckCount;
	delete [] mainDeck;
}

Deck& Deck::operator=(const Deck& rhs) {
	if (this != &rhs) {
		mainDeckCount = new int(*rhs.mainDeckCount);
		mainDeck = new Card[*mainDeckCount];
		for (int i = 0; i < *mainDeckCount; i++) {
			mainDeck[i] = Card(rhs.mainDeck[i]);
		}
	}
	return *this;
}

int Deck::getDeckSize() {
	return *mainDeckCount;
}

void Deck::removeCard(int index) {
	remove(mainDeck, *mainDeckCount, index);
}

Card Deck::draw() {
	if (*mainDeckCount > 0) {
		// remove the last card in the deck and return it
		return pop(mainDeck, *mainDeckCount);
	}
	return Card();  // Return blank card if the deck is empty
}

void Deck::addCard(Card card) {
	push(mainDeck, *mainDeckCount, card);
}

ostream& operator<<(ostream& out, const Deck& D) {
	Deck& cD = const_cast <Deck&>(D);
	
	out << "Deck contains: " << endl;
	for (int i = 0; i < cD.getDeckSize(); i++) {
		out << cD.mainDeck[i] << endl; // Use the stream insertion operator from the Card class
	}
	return out;
}

// - Hand functions -

Hand::Hand(Deck& deck) : sharedDeck(deck) {}

// (deep copy of handCards, but sharedDeck remains a reference)
Hand::Hand(const Hand& rhs) : sharedDeck(rhs.sharedDeck) {
	cardsCount = new int(*rhs.cardsCount);
	handCards = new Card[*cardsCount];
	for (int i = 0; i < *cardsCount; i++) {
		handCards[i] = Card(rhs.handCards[i]);
	}
}

Hand& Hand::operator=(const Hand& rhs) {
	if (this != &rhs) {
		cardsCount = new int(*rhs.cardsCount);
		handCards = new Card[*cardsCount];
		for (int i = 0; i < *cardsCount; i++) {
			handCards[i] = Card(rhs.handCards[i]);
		}
		// Reference to the shared deck remains unchanged (sharedDeck is not reassigned)
	}
	return *this;
}

Hand::~Hand() {
	delete cardsCount;
	delete [] handCards;
}

void Hand::drawCard() {
	Card drawnCard = Card(sharedDeck.draw());
	if (drawnCard.getCardType() != Card::blank) {
		push(handCards, *cardsCount, drawnCard);
		cout << "Card drawn and added to hand." << drawnCard << endl;
	}
	else {
		cout << "The deck is empty, no card drawn." << endl;
	}
}

void Hand::playCard(int index) {
	if (index >= 0 && index < *cardsCount) {
		Card cardToPlay = remove(handCards, *cardsCount, index);

		// Play the card (assuming the Card class has a `play` method)
		cardToPlay.play();

		// Add the played card back to the deck
		sharedDeck.addCard(cardToPlay);

		cout << "Card played and added back to the deck." << endl;
	}
	else {
		cout << "Invalid index. No card played." << endl;
	}
}

void Hand::showHand() const {
	cout << "Hand contains: " << endl;
	for (int i = 0; i < *cardsCount; i++) {
		cout << (i + 1) << ": " << handCards[i] << endl; // Assuming Card class has a stream operator defined
	}
}

ostream& operator<<(ostream& out, const Hand& H) {
	Hand& cH = const_cast <Hand&>(H);
	
	out << "Hand contains: ";
	for (int i = 0; i < *cH.cardsCount; i++) {
		if (i != 0) { out << ", "; };
		out << cH.handCards[i]; // Use the stream insertion operator from Card class
	}
	out << endl;
	return out;
}

#endif