#pragma once
#include <vector>

enum cardType {infantry,artillery,cavalry}; //enum 3 type of cards

class Card {
public:
	Card(cardType t);
	void display();
	cardType getType();
	void myDestructor();
	~Card();
	//why two destructor: when the deckVector is created, I will use 'temp' as variable name to  new a Card object to push,
	//however when the 'temp' point to another object, the former one will call destructructor automatically;
private:
	cardType* type;
};

class Deck {
private:
	int* numOfInf;
	int* numOfCav;
	int* numOfArt;
	std::vector<Card> *deckVector;
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
	std::vector<Card> *handDeck;
public:
	Hand();
	~Hand();
	bool exchange();
	void draw(Deck *d);
	void display();//This display will show the number of different kinds of cards  in hand
	void displayCurrentCard();//This display will show current card object in hand
	int getTotalCards();
	int getArmyCounter();
};
