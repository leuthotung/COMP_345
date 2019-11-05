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
class Country;
class Continent;
class Map;
class Player {

private:
	string* name;    //pointer
	vector<Country*> countries; //Collection of countries
	Dice* dice; // Dice facility
	Hand* hand;    //Hand of Risk cards
	vector<Continent*> continentsOwned;
	Map* gameMap;


public:
	Player();
	~Player();
	Player(string name);
	Hand* getHand();
	Dice* getDice();
	Map* getMap();
	void setMap(Map* map);
	void addCountry(Country* country);
	void removeCountry(Country* country);
	void reinforce();
	void attack();
	void fortify();
	string getName();
	vector<Country*> getCountries();
	bool hasOwnership(Continent* continent);
	int armiesFromContinent();
	void showInformation();
};

#endif
