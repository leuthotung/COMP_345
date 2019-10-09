//
// Created by tungleu on 9/26/19.
//

#include "Map.h"
#include <iostream>
#include <vector>
#include <queue>


using namespace std;
Country::Country(string countryName ,Continent continentName) {
    this->name = new string(countryName);
    this->numberOfArmies = new int(0);
    this->continent = &continentName;

}
string Country::getName() {
    return *name;
}


void Country::setName(string countryName) {
    this->name = &countryName;
}

Country::~Country() {

}

void Country::addNeighbor(Country country) {
    this->neighbors.push_back(&country);
}

vector<Country*> Country::getNeigbors() {
    return this->neighbors;
}

Continent::Continent(string continentName) {
    this->name = new string(continentName);
}

Continent::~Continent() {

}

string Continent::getName() {
    return *name;
}

void Continent::setName(string continentName) {
    this->name = &continentName;

}

void Continent::addCountry(Country country) {
    this->countries.push_back(&country);
}

Map::Map() {


}

Map::~Map() {

}
void Map::showMap() {

}

void Map::addContinent(Continent continent) {
    this->continents.push_back(&continent);
}



Continent Map::getContinentbyIndex(int index) {
    return *this->continents[index];
}

void Map::addCountry(Country country) {
    this->countries.push_back(&country);
}

Country Map::getCountrybyIndex(int index) {
    return *this->countries[index];
}
// Using BFS algorithm to show the map is connected or not
bool Map::isConnected(Country country) {
    country = this->getCountrybyIndex(0);
    bool *visited = new bool[this->countries.size()];
    for(int i = 0; i< this->countries.size();i++)
        visited[i] = 0;
    queue<Country> queue;
    visited[getIndexOfCountry(&country)]= true;
    queue.push(country);
    while(!queue.empty()){
        country = queue.front();
        queue.pop();
        vector<Country*> neighbors = country.getNeigbors();
        for(auto & neighbor : neighbors){
            if(!visited[getIndexOfCountry(neighbor)]){
                visited[getIndexOfCountry(neighbor)]= true;
                queue.push(*neighbor);
            }
        }
    }


}


int Map::getIndexOfCountry(Country *country) {
    for(int i = 0; i< this->countries.size();i++){
        if (countries[i] == country) {
            return i;
        }


    }
}
