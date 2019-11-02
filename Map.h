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
    Country();
    Country(string name,  Continent* continent);
    ~Country();
    string getName();
    vector<Country*> getNeigbors();
    void addNeighbor(Country* country);
    void setName(string countryName);
	Continent getContinent();//assignment2 ok
	void addArmy(int changeArmy);
	int getArmies();
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

};

class Continent{
//Attributes
private:
    string* name;
    vector<Country*> countries;
public:
    Continent(string continentName);
    ~Continent();
    string getName();
    void setName(string continentName);
    void addCountry(Country* country);
    bool isConnected();
    Country* getCountrybyIndex(int index);
    int getIndexOfCountry(Country* country);


};

#endif //COMP345_MAP_H
