
#include <string>
#include "Map.h"
#include <list>
#include "GameObservers.h"
#include "Player.h"
using namespace std;

static void clear(){
    for (int i = 0; i<50;i++){
        cout<<"\n";
    }
}
Subject::Subject() {
    _observers = new list<GameObservers*>;
}
Subject::~Subject() {
    delete _observers;
}
void Subject::Attach(GameObservers* o) {
    _observers->push_back(o);
};
void Subject::Detach(GameObservers* o) {
    _observers->remove(o);
};

void Subject::Notify() {
    list<GameObservers*>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update();
};






Player::Player(string name) {
    this->name = new string(name);
    this->hand = new Hand();
    this->dice = new Dice();
    this->phase = new string("null");
    this->observerSelect = new int(2);
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
    clear();
    *phase = "Reinforce";
    *observerSelect = 2;
    Notify();
    this->strategies->reinforce(this);
}

void Player::attack() {
    clear();
    *phase = "Attack";
    *observerSelect = 2;
    Notify();
    this->strategies->attack(this);
}

void Player::fortify() {
    clear();
    *phase = "Foritify";
    *observerSelect=2;
    Notify();
    this->strategies->fortify(this);
}

void Player::setStrategy(PlayerStrategies* strat) {
    strategies = strat;

}

void Player::chooseStrategy() {
    int number;
    cout<<"Player "<< this->getName() << " please choose one of five strategies: " <<endl;
    cout<<"1. Human"<<endl;
    cout<<"2. Aggressive"<<endl;
    cout<<"3. Benevolent"<<endl;
    cout<<"4. Random"<<endl;
    cout<<"5. Cheater"<<endl;
    while(true) {
        cin>>number;
        if (number == 1) {
            this->setStrategy(new Human());
            cout<<" Human strategy has been chosen"<<endl;
            break;
        } else if (number == 2) {
            this->setStrategy(new Aggressive());
            cout<<" Aggressive strategy has been chosen"<<endl;
            break;
        } else if (number == 3) {
            this->setStrategy(new Benevolent);
            cout<<" Benevolent strategy has been chosen"<<endl;
            break;
        }else if (number == 4) {
            this->setStrategy(new Random);
            cout<<" Random strategy has been chosen"<<endl;
            break;
        }else if (number == 5) {
            this->setStrategy(new Cheater);
            cout<<" Cheater strategy has been chosen"<<endl;
            break;
        }
        else{
            cout<<"Invalid number please choose again !!"<<endl;
        }
    }



}

int Player::getObserverSelect() {
    return *observerSelect;
}

string Player::getPhase() {
    return *phase;
}

vector<Player*> Player::getPlayers() {
    return players;
}

void Player::setPlayers(vector <Player*> gamePlayers) {
    players = gamePlayers;
}

void Player::setObserverSelect(int i ) {
    *observerSelect = i;

}

PlayerStrategies* Player::getStrategy() {
    return this->strategies;
}