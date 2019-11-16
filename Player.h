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
#include <list>

using namespace std;

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	list<Observer*>* _observers;
};

// forward declaration (circular dependency)
class Country;
class Continent;
class Map;




class Player:public Subject {

private:
	int* observerSelect;
	string* name;    //pointer
	string* phase;
	vector<Country*> countries; //Collection of countries
	Dice* dice; // Dice facility
	Hand* hand;    //Hand of Risk cards
	vector<Continent*> continentsOwned;
	Map* gameMap;
	vector<Player*> players;

public:
	Player();
	~Player();
	Player(string name);
	Hand* getHand();
	Dice* getDice();
	Map* getMap();
	void setMap(Map* map);
	vector<Player*> getPlayers();
	void setPlayers(vector<Player*> player);
	void addCountry(Country* country);
	void removeCountry(Country* country);
	int getObserverSelect();
	void reinforce();
	void attack();
	void fortify();
	string getName();
	string getPhase();
	vector<Country*> getCountries();
	bool hasOwnership(Continent* continent);
	int armiesFromContinent();
	void showInformation();
};

#endif
