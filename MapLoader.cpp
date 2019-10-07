//
// Created by tungleu on 9/27/19.
#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <fstream>
using namespace std;
Map readMapFile(string file) {
    Map map;
    string line;
    bool hasContinents = false;
    bool hasCountries = false;
    bool hasBorders = false;
    //input file
    ifstream inputFile(file);
    //Check if file exists
    if (inputFile.fail()){
        cerr<<"Error opening file"<<endl;
        exit(1);
    }
    else {
        //Check if the map file is valid.
        while (!inputFile.eof()) {
            inputFile >> line;
            if (line == "[continents]") {
                hasContinents = true;
            }
            if (line == "[countries]") {
                hasCountries = true;
            }
            if (line == "[borders]") {
                hasBorders = true;
            }
        }
        if ((hasContinents && hasCountries && hasBorders) == false) {
            cerr << "The map file is not valid" << endl;
            exit(1);
        }
    }

}
