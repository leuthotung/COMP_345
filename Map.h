//
// Created by tungleu on 9/26/19.
//
#ifndef COMP345_MAP_H
#define COMP345_MAP_H
#include <iostream>
#include <vector>
using namespace std;
class Continent;
class Country{
//Attributes
private:
    int* numberOfArmies;
    string* name;
    vector<Country*> neighbors;
    Continent* continent;
public:
    Country(string name,  Continent continent);
    ~Country();
    string getName();
    void addNeighbor(Country country);
    void setName(string countryName);

};
class Map{
//Attributes
private:
    vector<Country*> countries;
    vector<Continent*> continents;
public:
    Map();
    ~Map();
    void addCountry();
    void addContinent();
    void showMap();


};

class Continent{
//Attributes
private:
    string* name();
    vector<Country*> countries;
public:
    Continent();
    ~Continent();
};

#endif //COMP345_MAP_H
