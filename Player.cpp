#include "Player.h"
#include <string>
#include "Map.h"

using namespace std;

Player::Player(string name) {
    this->name = new string(name);
    this->hand = new Hand();
    this->dice = new Dice();
}

Player::Player() {

}

Player::~Player() {

}

Map *Player::getMap() {
    return gameMap;
}

void Player::setMap(Map *map) {
    gameMap = map;
}

void Player::addCountry(Country* newCountry) {
    countries.push_back(newCountry);
    newCountry->setOwner(this);
}

void Player::removeCountry(Country *country) {
    for (int i = 0; i < countries.size(); i++)
    {
        if (countries.at(i)->getName() == country->getName())
        {
            countries.erase(countries.begin() + i);
            break;
        }
    }
    cout << *name << " just lost this Country " << country->getName() << endl;

}

Dice *Player::getDice() {
    return this->dice;
}

Hand *Player::getHand() {
    return this->hand;
}

string Player::getName() {
    return *name;
}
vector<Country*> Player::getCountries(){
    return countries;
}
// This method show current information of the countries this Player owns
void Player::showInformation() {
    for (int i = 0; i < countries.size(); i++) {
        cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getNumberOfArmies() << endl;
    }
}
//This method checks if player has ownership of the continent
bool Player::hasOwnership(Continent* continent) {
    int countryCounter = 0;
    for(int i = 0; i< this->countries.size(); i++){
        if(countries[i]->getContinent() == continent)
            countryCounter++;
    }
    return(countryCounter == continent->getCountries().size());
}
//This method returns number of armies that Player can have from occupying continents
int Player::armiesFromContinent() {
    int armiesToAdd = 0;
    vector<Continent*> continents=  this->getMap()->getContinents();
    for(int i = 0; i < continents.size(); i++){
        if(this->hasOwnership(continents[i])){
            armiesToAdd += continents[i]->getValue();
            cout<<continents[i]->getValue()<<" armies added since "<< this->getName() <<" owns this Continent: "<<continents[i]->getName();
        }
    }
    return armiesToAdd;

}
void Player::reinforce() {
    this->strategies->reinforce(this);
}

void Player::attack() {
    this->strategies->attack(this);
}

void Player::fortify() {
    this->strategies->fortify(this);
}

void Player::setStrategy(PlayerStrategies* strat) {
    strategies = strat;

}

void Player::chooseStrategy() {
    int number;
    cout<<"Player "<< this->getName() << " please choose one of three strategies: " <<endl;
    cout<<"1. Human"<<endl;
    cout<<"2. Aggresive"<<endl;
    cout<<"3. Benevolent"<<endl;
    while(true) {
        cin>>number;
        if (number == 1) {
            this->setStrategy(new Human());
            cout<<" Human strategy has been chosen"<<endl;
            break;
        } else if (number = 2) {
            this->setStrategy(new Aggresive());
            cout<<" Aggressive strategy has been chosen"<<endl;
            break;
        } else if (number = 3) {
            this->setStrategy(new Benevolent);
            cout<<" Benevolent strategy has been chosen"<<endl;
            break;
        }
        else{
            cout<<"Invalid number please choose again !!"<<endl;
        }
    }



}











