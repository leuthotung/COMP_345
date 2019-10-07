//
// Created by tungleu on 9/26/19.
//

#include "Map.h"
#include <iostream>
#include <vector>
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

Continent::Continent() {

}

Continent::~Continent() {

}

Map::Map() {


}

Map::~Map() {

}
void Map::showMap() {

}

void Map::addContinent() {

}

void Map::addCountry() {

}
