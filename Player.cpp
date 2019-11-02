#include "Player.h"
#include <string>
using namespace std;

Player::Player(string name) {
    this->name = new string(name);
    this->hand = new Hand();
    this->dice = new Dice();
	this->armyCounter = new int(0);
	this->asiaCounter = new int(0);
	this->euCounter = new int(0);
	this->naCounter = new int(0);
	this->saCounter = new int(0);
	this->africaCounter = new int(0);
	this->oceaniaCounter = new int(0);
}

Player::Player() {

}

Player::~Player() {

}

void Player::reinforce() {
	bool exchangeFlag = false;
	int countryIndex = 0;
	int addArmy = 0;
	cout << "------------------REINFORCE START-------------------------" << endl;
	*armyCounter += this->countries.size() / 3;
	*armyCounter += continentCheck();
	cout << "Do you want to exchange card??(intput 0(false) or 1(true) )" << endl;
	cin >> exchangeFlag;
	if (exchangeFlag == true)
		* armyCounter += this->hand->exchange();
	cout << "will get " << *armyCounter << " armies  in reinforce stage"<<endl;
	cout << "--------------------This is your information-----------------------" << endl;
	for (int i = 0; i < countries.size(); i++) {
		cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getArmies() << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
	while (*armyCounter > 0)
	{
		countryIndex = 0;
		addArmy = 0;
		cout << "there are " << *armyCounter << "armies need to be place"<<endl;
		cout << "Firstly, choose the index of country you want to change"<<endl;
		cin >> countryIndex;
		if (countryIndex<0 || countryIndex>countries.size() - 1)
		{
			cout << "invalid input" << endl;
			continue;
		}
		cout << "Secondly, choose the number of armies you want to place"<<endl;
		cin >> addArmy;
		if (addArmy < 0 || *armyCounter - addArmy < 0)
		{
			cout << "invalid input" << endl;
			continue;
		}
		countries[countryIndex]->addArmy(addArmy);
		*armyCounter -= addArmy;
	}
	cout << "all armies are placed successfully" << endl; 
	cout << "--------------------This is your information-----------------------" << endl;
	for (int i = 0; i < countries.size(); i++) {
		cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getArmies() << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
	cout << "--------------------REINFORCE END--------------------------" << endl;
}

void Player::attack() {
    cout<<"Attack"<<endl;

}

void Player::fortify() {
    cout<<"Fortified"<<endl;

}

int Player::continentCheck()
{
	int tempCounter = 0;
	if (*asiaCounter == 5) //5 means 5 countries in asia
		tempCounter += 3; // control value
	if (*euCounter == 6)
		tempCounter += 3; // control value
	if (*saCounter == 7)
		tempCounter += 3; // control value
	if (*naCounter == 2)
		tempCounter += 3; // control value
	if (*africaCounter == 9)
		tempCounter += 3; // control value
	if (*oceaniaCounter == 10)
		tempCounter += 3; // control value
	return tempCounter;
}

void Player::addCountry(Country* newCountry) {
    countries.push_back(newCountry);
	if (newCountry->getContinent().getName().compare("asia") == 0) {
		++*asiaCounter;
	}
	else if (newCountry->getContinent().getName().compare("europe") == 0)
		++*euCounter;
	else if (newCountry->getContinent().getName().compare("northAmerica") == 0)
		++*naCounter;
	else if (newCountry->getContinent().getName().compare("southAmerica") == 0)
		++*saCounter;
	else if (newCountry->getContinent().getName().compare("africa") == 0)
		++*africaCounter;
	else if (newCountry->getContinent().getName().compare("oceania") == 0)
		++*oceaniaCounter;
}

Dice *Player::getDice() {
    return this->dice;
}

Hand *Player::getHand() {
    return this->hand;
}


