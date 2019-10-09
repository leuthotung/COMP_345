#pragma once
#include <vector>
enum cardType {infantry,artillery,cavalry};

class Card {
public:
	Card(cardType t);
	void display();
	char getType();
private:
	cardType* type;
};

class Deck {
private:
	int* numOfInf;
	int* numOfCav;
	int* numOfArt;
	std::vector<Card> *deckArrayList;
public:
	Deck(int numberOfCountries);
	~Deck();
	Card draw();
	void display(); 
};

class Hand {
	int* numOfInf;
	int* numOfCav;
	int* numOfArt;
	int* totalNumOfCards;
	int* armyCounter;
public:
	Hand();
	~Hand();
	bool exchange();
	void draw(Deck *d);
	void display();
	int getTotalCards();
	int getArmyCounter();
};
