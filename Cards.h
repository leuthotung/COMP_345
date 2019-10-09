#pragma once
#include <vector>


class Card {
public:
	Card(char t);
	void display();
	char getType();
private:
	char* type;
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
