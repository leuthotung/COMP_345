//
// Created by tungleu on 9/27/19.
#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
bool validateMapFile(string file){
    ifstream checkValid(file);
    string lineCheck;
    bool hasContinents = false;
    bool hasCountries = false;
    bool hasBorders = false;
    while(getline(checkValid,lineCheck)){
        if(lineCheck == "[continents]\r") {
            hasContinents = true;
            while(getline(checkValid,lineCheck) &&lineCheck != "\r"){
                stringstream ss(lineCheck);
                string word;
                char delim = ' ';
                vector<string> lineSplit;
                while (getline(ss, word, delim)) {
                    lineSplit.push_back(word);
                }
                //check if it has enough information
                if (lineSplit.size() != 3)
                    cerr<<"Incorrect continent format"<<endl;
                //check if it is an intergrer
                try{
                    int value = stoi(lineSplit[1]);
                }
                catch(...){
                    cerr<<"Incorrect continent format"<<endl;
                }


            }
        }
        if(lineCheck == "[countries]\r") {
            hasCountries = true;
            while (getline(checkValid, lineCheck) && lineCheck != "\r") {
                stringstream ss(lineCheck);
                string word;
                char delim = ' ';
                vector<string> lineSplit;
                while (getline(ss, word, delim)) {
                    lineSplit.push_back(word);
                }
                //check if the line has enough information
                if (lineSplit.size() != 5)
                    cerr<<"Incorrect country format"<<endl;
                //Check if they are intergers
                try{
                    int value = stoi(lineSplit[0]);
                    int value2 = stoi(lineSplit[2]);
                    int value3 = stoi(lineSplit[3]);
                    int value4 = stoi(lineSplit[4]);
                }
                catch(...){
                    cerr<<"Incorrect country format"<<endl;
                }
            }
        }
        if(lineCheck == "[borders]\r"){
            hasBorders = true;
            while (getline(checkValid, lineCheck) && lineCheck != "\r") {
                stringstream ss(lineCheck);
                string word;
                char delim = ' ';
                vector<string> lineSplit;
                while (getline(ss, word, delim)) {
                    lineSplit.push_back(word);
                }
                //check if they are all numbers
                try{
                    for (int i = 0; i < lineSplit.size(); i++) {
                        int value = stoi(lineSplit[i]) ;
                    }
                }
                catch(...){
                    cerr<<"Incorrect borders format"<<endl;
                }
            }
        }


    }
    bool enoughSections= hasBorders && hasContinents && hasCountries;
    return enoughSections;

}

Map readMapFile(string file) {
   bool validate = validateMapFile(file);
   if(validate == true) {
       try {
           Map map;
           ifstream inputFile(file);
           string line;
           //Find the [continents] section
           while (getline(inputFile, line) && line != "[continents]\r") {}
           while (getline(inputFile, line) && line != "\r") {
               //cout << line << endl;
               string continent = line.substr(0, line.find(" "));
               int value = stoi(line.substr(line.find(" ") + 1)); //will take care of the value later
               map.addContinent(new Continent(continent,value));
               //cout<<continent<<" and " << value <<endl;
           }
           //Find the [countries[ section
           while (getline(inputFile, line) && line != "[countries]\r") {}
           while (getline(inputFile, line) && line != "\r") {
               //split the line
               stringstream ss(line);
               string word;
               char delim = ' ';
               vector<string> lineSplit;
               while (getline(ss, word, delim)) {
                   lineSplit.push_back(word);
               }
               int continentIndex = stoi(lineSplit[2]) - 1;
               //add a country to the map
               map.addCountry(new Country(lineSplit[1], map.getContinentbyIndex(continentIndex)));
               int countryIndex = stoi(lineSplit[0]) - 1;
               //add country to the continent as well
               map.getContinentbyIndex(continentIndex)->addCountry(map.getCountrybyIndex(countryIndex));

           }

           //Find [borders] section
           while (getline(inputFile, line) && line != "[borders]\r") {}
           while (getline(inputFile, line) && line != "\r") {
               stringstream ss(line);
               string word;
               char delim = ' ';
               vector<string> lineSplit;
               while (getline(ss, word, delim)) {
                   lineSplit.push_back(word);
               }
               int countryIndex = stoi(lineSplit[0]) - 1;
               for (int i = 1; i < lineSplit.size(); i++) {
                   int indexToAdd = stoi(lineSplit[i]) - 1;
                   map.getCountrybyIndex(countryIndex)->addNeighbor(map.getCountrybyIndex(indexToAdd));
               }

           }
           map.setDeck(map.getCountries().size());

           return map;
       }
       catch (...){
           cerr<<"There are some error in the Map file"<<endl;
       }
   }
   else{
       cerr<<"Map is not valid since this Map doens have enough required section"<<endl;
       return Map();
   }

}
