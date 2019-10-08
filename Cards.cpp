#include "./cards.h"

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono> 
using namespace std;


Card::Card(cardType t) {
	this->type = t;
}

void Card::display(){
	if (this->type==INFANTRY)  
		cout<<"infantry"<<endl;
	else if (this->type == CAVALRY)
		cout << "Cavalry"<<endl;
	else if (this->type == ARTILLERY)
		cout << "Artillery"<<endl;
	}



Deck::Deck(int numberOfCountries) {
	this->numOfArt = numberOfCountries / 3;
	this->numOfInf = numberOfCountries / 3;
	this->numOfCav = numberOfCountries / 3;
	vector<Card> DeckArrayList;
	if (numberOfCountries % 3 == 1)
	{
		numOfArt++;
	}
	if (numberOfCountries % 3 == 2)
	{ 
		numOfArt++;
	    numOfCav++;
	}
	for (int i = 0; i < numOfInf; i++) {
		DeckArrayList.push_back(Card(INFANTRY));
	}
	for (int i = 0; i < numOfCav; i++) {
		DeckArrayList.push_back(Card(CAVALRY));
	}
	for (int i = 0; i < numOfArt; i++) {
		DeckArrayList.push_back(Card(ARTILLERY));
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(DeckArrayList.begin(),DeckArrayList.end(),e); //shuffle the deck
	
	for (int i = 0; i < DeckArrayList.size(); i++) {
		DeckArrayList[i].display();
	} //at this step is perfect.


}

void Deck::getDECKDATA()
{
	cout<<DeckArrayList.size()<<endl;
}



/*	

Card* Deck::draw() {
	if (this->getCurrentNumOfCards() > 0) {
	    Card* DeckArrayList = &DeckArrayList.back();
		if (DeckArrayList->type==ARTILLERY) {
			numOfArt - 1;
		}
		if (DeckArrayList->type == INFANTRY) {
			numOfInf - 1;
		}
		if (DeckArrayList->type == CAVALRY) {
			numOfCav - 1;
		}
        DeckArrayList.pop_back();
		return DeckArrayList;
	}
	return NULL;
}
*/
void Deck::display() {
	cout << "The deck contains " << numOfArt << " artillery, " << numOfCav << " cavalry, and " << numOfInf << " infantry." << endl;
}

Hand::Hand() 
{   
	this->armyCounter = 0;
	this->numOfArt = 0;
	this->numOfCav = 0;
	this->numOfInf = 0;
	this->totalNumOfCards = 0;
}
Hand::Hand(int inf, int cav, int art)
{
	this->armyCounter = 0;
	this->numOfInf = inf;
	this->numOfCav = cav;
	this->numOfArt = art;
	this->totalNumOfCards=art+cav+inf;
}
;

bool Hand::exchange() {
	if (numOfArt >= 3) {
		numOfArt -= 3;
		totalNumOfCards -= 3;
		armyCounter += 5;
		return true;
	}
	else if (numOfCav >= 3) {
		numOfCav -= 3;
		totalNumOfCards -= 3;
		armyCounter += 5;
		return true;
	}
	else if (numOfInf >= 3) {
		numOfInf -= 3;
		totalNumOfCards -= 3;
		armyCounter += 5;
		return true;
	}
	else if (numOfArt >= 1 && numOfCav >= 1 && numOfInf >= 1) {
		numOfArt -= 1;
		numOfCav -= 1;
		numOfInf -= 1;
		totalNumOfCards -= 3;
		armyCounter += 5;
		return true;
	}
	else
		return false;
}
/*
void Hand::draw(Deck* d) {
	Card* c=d->draw();
	if (c->type == INFANTRY)
		numOfInf++;
	if (c->type == ARTILLERY)
		numOfArt++;
	if (c->type == CAVALRY)
		numOfCav++;
	delete c;
}
*/
int Hand::getTotalCards() {
	return totalNumOfCards;
}

int Hand::getArmyCounter() {
	return armyCounter;
}

void Hand::display() {
	cout << "This hand contains " <<this->totalNumOfCards<<"cards,"<< this->numOfInf << " infantry cards, " << this->numOfCav << " cavalry cards, and "
		<< this->numOfArt << " artillery cards." << endl;
}
