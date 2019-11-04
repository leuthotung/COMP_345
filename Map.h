//
// Created by tungleu on 9/26/19.
//
#ifndef COMP345_MAP_H
#define COMP345_MAP_H
#include <iostream>
#include <vector>
#include "Player.h"
using namespace std;
class Continent;
class Player;
class Country{
//Attributes
private:
    int* numberOfArmies;
    string* name;
    vector<Country*> neighbors;
    Continent* continent;
    Player* owner;
public:
    Country();
    Country(string name,  Continent* continent);
    ~Country();
    string getName();
    vector<Country*> getNeigbors();
    int getNumberOfArmies();
    Player* getOwner();
    Continent* getContinent();
    void addNeighbor(Country* country);
    void setName(string countryName);
    void addArmies(int number);
    void setOwner(Player* owner);



};
class Map{
//Attributes
private:
    vector<Country*> countries;
    vector<Continent*> continents;
public:
    Map();
    ~Map();
    Continent* getContinentbyIndex(int index);
    Country* getCountrybyIndex(int index);
    void addCountry(Country* country);
    void addContinent(Continent* continent);
    void showMap();
    bool isConnected();
    int getIndexOfCountry(Country *country);
    void print();
    vector<Continent*> getContinents();
    vector<Country*> getCountries();


};

class Continent{
//Attributes
private:
    string* name;
    vector<Country*> countries;
    int *value;
public:

    Continent(string continentName, int value);
    ~Continent();
    string getName();
    void setName(string continentName);
    void addCountry(Country* country);
    bool isConnected();
    Country* getCountrybyIndex(int index);
    int getIndexOfCountry(Country* country);
    vector<Country*> getCountries();
    int getValue();



};

#endif //COMP345_MAP_H
