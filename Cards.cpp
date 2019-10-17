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
//why two destructor: when the deck is created, I will use 'temp' as variable name to create new Card to push,however when the 'temp' point to another object, the former one will be destruct automatically;
Card::~Card() {
}

void Card::myDestructor() {
	delete type;
	type = NULL;
}
void Card::display(){
	if (*type == infantry)
		cout << "Infantry" << endl;
	else if (*type == cavalry)
		cout << "Cavalry" << endl;
	else if (*type == artillery)
		cout << "Artillery" << endl;
	}

cardType Card::getType()
{
	return *type;
}



Deck::Deck(int numberOfCountries) {
	this->numOfArt =new int(numberOfCountries / 3); //get  the integer part
	this->numOfInf =new int(numberOfCountries / 3);
	this->numOfCav =new int(numberOfCountries / 3);
	deckVector=new vector<Card>; 
	if (numberOfCountries % 3 == 1) // when the number of countries are not multiple of 3
	{
		*numOfArt=*numOfArt+1;
	}
	if (numberOfCountries % 3 == 2)
	{ 
		*numOfArt = *numOfArt + 1;
	    *numOfCav=*numOfCav +1;
	}
	for (int i = 0; i < *numOfInf; i++) { //emplace_back is push_back;emplace_back avoids the extra copy or move operation required when using push_back.
		deckVector->emplace_back(*new Card(infantry));
	}
	for (int i = 0; i < *numOfCav; i++) {
		deckVector->emplace_back(*new Card(cavalry));
	}
	for (int i = 0; i < *numOfArt; i++) {
		deckVector->emplace_back(*new Card(artillery));
	}
	//shuffle the deck randomly
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::shuffle(deckVector->begin(),deckVector->end(),e); //shuffle the deck
	cout << "Deck created" << endl;
	/*for demo use
	for (int i = 0; i < deckVector->size(); i++) {
		deckVector->at(i).display();
	}
	*/ 
}

Deck::~Deck()
{
}




	
//the function will draw a card from the deckArrayList,but it won't destroy the card Object
Card Deck::draw() {
	if (this->deckVector->size() > 0) {
		Card* myCard = &deckVector->back();
		if (myCard->getType() == artillery) {
			*numOfArt -= 1;
		}
		if (myCard->getType() == infantry) {
			*numOfInf -= 1;
		}
		if (myCard->getType() == cavalry) {
			*numOfCav -= 1;
		}
		deckVector->pop_back();
		return *myCard;
	}
	else
		cout << "no card in deck" << endl;
	}

void Deck::display() {
	cout << "The deck contains " << *numOfArt << " artillery, " << *numOfCav << " cavalry, and " << *numOfInf << " infantry." << "size is " << deckVector->size()<< endl;
}


Hand::Hand() 
{   
	this->armyCounter = new int(0);//initial armyCounter as 0, every exchange will let it+=5 then exchange;
	this->numOfArt = new int(0);
	this->numOfCav = new int(0);
	this->numOfInf = new int(0);
	this->totalNumOfCards = new int(0);
	handDeck = new vector<Card>;
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
	delete handDeck;
	handDeck = NULL;
	cout << "hand deleted" << endl;
}

bool Hand::exchangeFlag() {
	if (*numOfArt >= 3) 
	{
		*numOfArt -= 3;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		//why use for loop 3 times: cause the size is changing
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < handDeck->size(); i++) 
			{
				if (handDeck->at(i).getType() == artillery) 
				{
					handDeck->at(i).myDestructor();//erase doesn't have authority to delete the pointer
					handDeck->erase(handDeck->begin() + i);
					break;
				}
			}
		}
		return true;
	}
	else if (*numOfCav >= 3) 
	{
		*numOfCav -= 3;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < handDeck->size(); i++)
			{
				if (handDeck->at(i).getType() == cavalry)
				{
					handDeck->at(i).myDestructor();
					handDeck->erase(handDeck->begin() + i);
					break;
				}
			}
		}
		return true;
	}
	else if (*numOfInf >= 3) 
	{
		*numOfInf -= 3;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		for (int k = 0; k < 3; k++)
		{
			for (int i = 0; i < handDeck->size(); i++)
			{
				if (handDeck->at(i).getType() == infantry) {
					handDeck->at(i).myDestructor();
					handDeck->erase(handDeck->begin() + i);
					break;
				}
			}
		}
		return true;
	}
	else if (*numOfArt >= 1 && *numOfCav >= 1 && *numOfInf >= 1) {
		*numOfArt -= 1;
		*numOfCav -= 1;
		*numOfInf -= 1;
		*totalNumOfCards -= 3;
		*armyCounter += 5;
		for (int i = 0; i < handDeck->size(); i++) {
			if (handDeck->at(i).getType() == artillery) {
				handDeck->at(i).myDestructor();
				handDeck->erase(handDeck->begin() + i);
				break;
			}
		}
		for (int i = 0; i < handDeck->size(); i++) {
			if (handDeck->at(i).getType() == cavalry) {
				handDeck->at(i).myDestructor();
				handDeck->erase(handDeck->begin() + i);
				break;
			}
		}
		for (int i = 0; i < handDeck->size(); i++) {
			if (handDeck->at(i).getType() == infantry) {
				handDeck->at(i).myDestructor();
				handDeck->erase(handDeck->begin() + i);
				break;
			}
		}
		return true;
	}
	else
		return false;//there are no enought cards to exchange
}

int Hand::exchange()
{
	if (exchangeFlag() == true)
	{
		cout << "exchanged successfully," << *armyCounter << "armies will be returned" << endl;
		return *armyCounter;
	}
	else 
	{
		cout << "not enough card, won't exchange,0 army will be returned"<<endl;
		return 0;
	}
}

void Hand::draw(Deck *d) {
	if (*totalNumOfCards < 5) 
	{
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
		handDeck->push_back(c);// push the card to handVector
	}
	else//the num of cards in hand are above 5
	{
		cout<<"there are 5 cards in hand, exchange automatically"<<endl;
		exchange();
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
		handDeck->push_back(c);
	}
}

int Hand::getTotalCards() {
	return *totalNumOfCards;
}

int Hand::getArmyCounter() {
	return *armyCounter;
}

//This display will show the number of different kinds of cards  in hand
void Hand::display() {
	cout << "This hand contains " <<*totalNumOfCards<<"cards,"<< *numOfInf << " infantry cards, " << *numOfCav << " cavalry cards, and "
		<< *numOfArt << " artillery cards." <<"armyCounter is "<<getArmyCounter()<< endl;
}
//This display will show current card object in hand
void Hand::displayCurrentCard() {
	for (int i = 0; i < handDeck->size(); i++) {
		handDeck->at(i).display();
	}
}