//
// Created by tungleu on 10/11/19.
//
#include "MapLoader.h"
#include "Player.h"
#include <time.h>


int main(){
	srand(time(0));// This seeds the random number generator
    Player* Lebron =  new Player("Lebron");
	Player* abc = new Player("abc");
    Country* Canada = new Country("Canada",new Continent("northAmerica"));
	Country* USA = new Country("USA", new Continent("northAmerica"));
	Country* China = new Country("China", new Continent("asia"));
    Country* Japan = new Country("Japan", new Continent("asia"));
	Country* Korea = new Country("Korea", new Continent("asia"));
    Country* India = new Country("India", new Continent("asia"));
    Country* Vietnam = new Country("Vietnam", new Continent("asia")); 
	USA->addNeighbor(Canada);
	Canada->addNeighbor(USA);
	China->addNeighbor(Japan);
	China->addNeighbor(Korea);
	China->addNeighbor(India);
	Japan->addNeighbor(Korea);
	Japan->addNeighbor(China);
	Korea->addNeighbor(China);
	Korea->addNeighbor(Japan);
	India->addNeighbor(China);
	India->addNeighbor(Vietnam);
	Japan->addArmy(5); 
	India->addArmy(5);
	Vietnam->addNeighbor(India);
    Lebron->addCountry(Canada);
	Lebron->addCountry(USA);
	Lebron->addCountry(China);
	abc->addCountry(Japan);
	Lebron->addCountry(Korea);
	abc->addCountry(India);
	Lebron->addCountry(Vietnam);
	Deck* myDeck = new Deck(49);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->display();
	Lebron->reinforce();
	Lebron->attack();
	Lebron->fortify();
}

