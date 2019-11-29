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
#include "PlayerStrategies.h"
#include "GameObservers.h"
#include <list>
using namespace std;

// forward declaration (circular dependency)
class Country;
class Continent;
class Map;
class PlayerStrategies;
class GameObservers;

class Subject {
public:
    virtual void Attach(GameObservers* o);
    virtual void Detach(GameObservers* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:
    list<GameObservers*> *_observers;
};
class Player : public Subject {

private:
	string* name;    //pointer
	vector<Country*> countries; //Collection of countries
	Dice* dice; // Dice facility
	Hand* hand;    //Hand of Risk cards
	vector<Continent*> continentsOwned;
	Map* gameMap;
    PlayerStrategies *strategies;
    int* observerSelect;
    string* phase;
    vector<Player*> players;

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
	void setStrategy(PlayerStrategies* strat);
	void chooseStrategy();
	int getObserverSelect();
	string getPhase();
    vector<Player*> getPlayers();
    void setPlayers(vector<Player*> player);
    void setObserverSelect(int i);
    PlayerStrategies* getStrategy();

};

#endif
