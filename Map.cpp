//
// Created by tungleu on 9/26/19.
//

#include "Map.h"
#include <iostream>
#include <vector>
#include <queue>


using namespace std;
Country::Country(string countryName ,Continent* continentName) {
    this->name = new string(countryName);
    this->numberOfArmies = new int(1);
    this->continent = continentName;

}
string Country::getName() {
    return *name;
}


void Country::setName(string countryName) {
    this->name = &countryName;
}

Country::~Country() {

}

void Country::addNeighbor(Country* country) {
    this->neighbors.push_back(country);
}

vector<Country*> Country::getNeigbors() {
    return this->neighbors;
}

Country::Country() {

}

void Country::addArmies(int number) {
    *numberOfArmies = *numberOfArmies +number;
}

int Country::getNumberOfArmies() {
    return *numberOfArmies;
}


Player *Country::getOwner() {
    return owner;
}

void Country::setOwner(Player *player) {
    owner = player;
}

Continent *Country::getContinent() {
    return continent;
}



Continent::Continent(string continentName, int value) {
    this->name = new string(continentName);
    this->value = new int(value);
}

Continent::~Continent() {

}

string Continent::getName() {
    return *name;
}

void Continent::setName(string continentName) {
    *name = continentName;

}

void Continent::addCountry(Country* country) {
    this->countries.push_back(country);
}
// Using BFS to check if the continent is connected
bool Continent::isConnected() {
    Country* country = this->getCountrybyIndex(0);
    bool *visited = new bool[this->countries.size()];
    for(int i = 0; i< this->countries.size();i++)
        visited[i] = 0;
    queue<Country*> queue;
    int visitedCount = 1;
    visited[getIndexOfCountry(country)]= true;
    queue.push(country);
    while(!queue.empty()) {
        country = queue.front();
        queue.pop();
        vector<Country *> neighbors = country->getNeigbors();
        for (auto &neighbor : neighbors) {
            if (!visited[getIndexOfCountry(neighbor)]) {
                visited[getIndexOfCountry(neighbor)] = true;
                visitedCount++;
                queue.push(neighbor);
            }
        }
    }
    return visitedCount == this->countries.size();
}

Country *Continent::getCountrybyIndex(int index) {
    return this->countries[index];
}

int Continent::getIndexOfCountry(Country *country) {
    for(int i =0; i<this->countries.size();i++){
        if (countries[i] == country) {
            return i;
        }
    }
}

vector<Country *> Continent::getCountries() {
    return countries;
}

int Continent::getValue() {
    return *value;
}

Map::Map() {


}

Map::~Map() {

}
void Map::showMap() {

}

void Map::addContinent(Continent* continent) {
    this->continents.push_back(continent);
}



Continent* Map::getContinentbyIndex(int index) {
    return this->continents[index];
}

void Map::addCountry(Country* country) {
    this->countries.push_back(country);
}

Country* Map::getCountrybyIndex(int index) {
    return this->countries[index];
}
// Using BFS algorithm to show the map is connected or not
bool Map::isConnected() {

    Country *country = this->getCountrybyIndex(0);
    bool *visited = new bool[this->countries.size()];
    for(int i = 0; i< this->countries.size();i++)
        visited[i] = 0;
    queue<Country*> queue;
    int visitedCount = 1;
    visited[getIndexOfCountry(country)]= true;
    queue.push(country);
    while(!queue.empty()){
        country = queue.front();
        queue.pop();
        vector<Country*> neighbors = country->getNeigbors();
        for(auto & neighbor : neighbors){
            if(!visited[getIndexOfCountry(neighbor)]){
                visited[getIndexOfCountry(neighbor)]= true;
                visitedCount++;
                queue.push(neighbor);
            }
        }
    }
    return visitedCount == this->countries.size();


}


int Map::getIndexOfCountry(Country *country) {
    for(int i = 0; i< this->countries.size();i++){
        if (countries[i] == country) {
            return i;
        }

    }
}

void Map::print() {
    cout<< "LIST OF COUNTRIES :  "<<endl;
    Country* country;
    for (int i = 0; i< this->countries.size();i++){
        country = countries[i];
        cout<<country->getName()<<endl;
        cout<<"Neighbors: ";
        vector<Country*> neighbors = countries[i]->getNeigbors();
        for(int j = 0; j<neighbors.size();j++){
            cout<<neighbors[j]->getName()<<", ";
        }
        cout<<" "<<endl;
    }
    cout<< "LIST OF CONTINENTS: "<< endl;
    for (int i = 0; i< this->continents.size();i++){
        cout<<continents[i]->getName()<<endl;
    }

}

vector<Continent *> Map::getContinents() {
    return this->continents;
}

vector<Country *> Map::getCountries() {
    return this->countries;
}

void Map::setDeck(int numberOfCountries) {
    deck = new Deck(numberOfCountries);
}

Deck *Map::getDeck() {
    return deck;
}


Country *Map::getCountrybyName(string name) {
    Country * country;
    for(int i = 0; i< this->getCountries().size();i++){
        if(this->getCountries()[i]->getName() == name){
            country = this->getCountries()[i];
        }
    }
    return country;
}
