#pragma once
#include <vector>

enum cardType 
{ INFANTRY, CAVALRY, ARTILLERY };

class Card {
public:
	cardType type;
	Card(cardType t);
	void display();
};

class Deck {
private:
	int numOfInf;
	int numOfCav;
	int numOfArt;
	std::vector <Card> DeckArrayList;
public:
	Deck(int numberOfCountries);
	void getDECKDATA();
//	Card* draw();
	void display(); 
};

class Hand {
	int numOfInf;
	int numOfCav;
	int numOfArt;
	int totalNumOfCards;
	int armyCounter;
public:
	Hand();
	Hand(int inf,int cav, int art);
	bool exchange();
	//void draw(Deck* d);
	void display();
	int getTotalCards();
	int getArmyCounter();
};
