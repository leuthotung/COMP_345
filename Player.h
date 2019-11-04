#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Dice.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

// forward declaration (circular dependency)


class Player {

private:
	string* name;    //pointer
	vector<Country*> countries; //Collection of countries
	Dice* dice; // Dice facility
	Hand* hand;    //Hand of Risk cards
	int* armyCounter; //assignment2
	int* asiaCounter;
	int* euCounter;
	int* naCounter;
	int* saCounter;
	int* africaCounter;
	int* oceaniaCounter;

public:
	Player();
	~Player();
	Player(string name);
	Hand* getHand();
	Dice* getDice();
	string getName();
	void addCountry(Country* country);
	void removeCountry(Country* country);
	void reinforce();
	void attack();
	void fortify();
	int continentCheck();//assignment 2 ok
};

#endif
