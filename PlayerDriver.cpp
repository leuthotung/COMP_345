//
// Created by tungleu on 10/11/19.
//

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
	Japan->addNeighbor(Korea);
	Japan->addNeighbor(China);
	Korea->addNeighbor(China);
	Korea->addNeighbor(Japan);
	India->addNeighbor(Vietnam);
	Japan->addArmy(10);
	Vietnam->addNeighbor(India);
    Lebron->addCountry(Canada);
	Lebron->addCountry(USA);
	Lebron->addCountry(China);
	Lebron->addCountry(Japan);
	Lebron->removeCountry(Japan);
    abc->addCountry(Japan);
	Lebron->addCountry(Korea);
	Lebron->addCountry(India);
	Lebron->addCountry(Vietnam);
	cout <<Japan->getPlayer()->getName()<< endl;
	cout << "12345" << endl;
	Deck* myDeck = new Deck(49);
	//cout <<Lebron->continentCheck()<< endl;
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->display();
	Lebron->reinforce();
	Lebron->attack();
	Lebron->fortify();
	
/*	Lebron->getDice()->roll();
	for (int i = 0; i < Lebron->getDice()->get_value().size(); i++) {
		cout << *(Lebron->getDice()->get_value()[i]) << endl;
	}*/
}
