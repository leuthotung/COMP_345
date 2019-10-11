#include "./cards.h"

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono> 
using namespace std;


Card::Card(cardType t) {
	this->type =new cardType(t);
}


void Card::display(){
	if (*type == infantry)
		cout << "Infantry" << endl;
	else if (*type == cavalry)
		cout << "Cavalry" << endl;
	else if (*type == artillery)
		cout << "Artillery" << endl;
	}

char Card::getType()
{
	return *type;
}



Deck::Deck(int numberOfCountries) {
	this->numOfArt =new int(numberOfCountries / 3);
	this->numOfInf =new int(numberOfCountries / 3);
	this->numOfCav =new int(numberOfCountries / 3);
	Card* temp;
	deckArrayList=new vector<Card>;
	if (numberOfCountries % 3 == 1)
	{
		*numOfArt=*numOfArt+1;
	}
	if (numberOfCountries % 3 == 2)
	{ 
		*numOfArt = *numOfArt + 1;
	    *numOfCav=*numOfCav +1;
	}
	for (int i = 0; i < *numOfInf; i++) {
		temp= new Card(infantry);
		deckArrayList->push_back(*temp);
	}
	for (int i = 0; i < *numOfCav; i++) {
		temp = new Card(cavalry);
		deckArrayList->push_back(*temp);
	}
	for (int i = 0; i < *numOfArt; i++) {
		temp = new Card(artillery);
		deckArrayList->push_back(*temp);
	}
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(deckArrayList->begin(),deckArrayList->end(),e); //shuffle the deck
	cout << "Deck created" << endl;
}

Deck::~Deck()
{
	cout<<"deck deleted"<<endl;
}




	

Card Deck::draw() {
	if (this->deckArrayList->size() > 0) {
		Card* myCard = &deckArrayList->back();
		if (myCard->getType() == artillery) {
			*numOfArt -= 1;
		}
		if (myCard->getType() == infantry) {
			*numOfInf -= 1;
		}
		if (myCard->getType() == cavalry) {
			*numOfCav -= 1;
		}
		deckArrayList->pop_back();
		return *myCard;
	}
	else
		cout << "no card in deck" << endl;
	}

void Deck::display() {
	cout << "The deck contains " << *numOfArt << " artillery, " << *numOfCav << " cavalry, and " << *numOfInf << " infantry." << "size is " << deckArrayList->size()<< endl;
}

Hand::Hand() 
{   
	this->armyCounter = new int(0);
	this->numOfArt = new int(0);
	this->numOfCav = new int(0);
	this->numOfInf = new int(0);
	this->totalNumOfCards = new int(0);
	cout << "hand created" << endl;
}


Hand::~Hand() {
	delete armyCounter;
	delete numOfInf;
	delete numOfCav;
	delete numOfArt;
	delete totalNumOfCards;
	armyCounter = NULL;
	numOfInf = NULL;
	numOfCav = NULL;
	numOfArt = NULL;
	totalNumOfCards = NULL;
	cout << "hand deleted" << endl;
}

bool Hand::exchange() {
	if (*numOfArt >= 3) {
		*numOfArt -= 3;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		return true;
	}
	else if (*numOfCav >= 3) {
		*numOfCav -= 3;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		return true;
	}
	else if (*numOfInf >= 3) {
		*numOfInf -= 3;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		return true;
	}
	else if (*numOfArt >= 1 && *numOfCav >= 1 && *numOfInf >= 1) {
		*numOfArt -= 1;
		*numOfCav -= 1;
		*numOfInf -= 1;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		return true;
	}
	else
		return false;
}

void Hand::draw(Deck *d) {
	if (*totalNumOfCards < 5) {
		Card c = d->draw();
		if (c.getType() == infantry) {
			cout << "The drawing Card is infantry" << endl;
			*numOfInf += 1;
		}	
		if (c.getType() == artillery) {
			cout << "The drawing Card is artillery" << endl;
			*numOfArt += 1;
		}
		if (c.getType() == cavalry) {
			*numOfCav += 1;
			cout << "The drawing Card is calvalry" << endl;
		}
			
		*totalNumOfCards += 1;
	}
	else
	{
		exchange();
		cout<<"there are 5 cards in hand, exchange first"<<endl;
		Card c = d->draw();
		if (c.getType() == infantry) {
			cout << "The drawing Card is infantry" << endl;
			*numOfInf += 1;
		}
		if (c.getType() == artillery) {
			cout << "The drawing Card is artillery" << endl;
			*numOfArt += 1;
		}
		if (c.getType() == cavalry) {
			*numOfCav += 1;
			cout << "The drawing Card is calvalry" << endl;
		}
		*totalNumOfCards += 1;
	}
}

int Hand::getTotalCards() {
	return *totalNumOfCards;
}

int Hand::getArmyCounter() {
	return *armyCounter;
}

void Hand::display() {
	cout << "This hand contains " <<*totalNumOfCards<<"cards,"<< *numOfInf << " infantry cards, " << *numOfCav << " cavalry cards, and "
		<< *numOfArt << " artillery cards." <<"armyCounter is "<<getArmyCounter()<< endl;
}
