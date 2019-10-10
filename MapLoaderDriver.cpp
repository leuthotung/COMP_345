//
// Created by tungleu on 10/6/19.
//
#include "Map.h"
#include "MapLoader.h"

using namespace std;

int main() {
    Map a = readMapFile("/home/tungleu/CLionProjects/COMP_345/Maps/europe.map");
    //a.print();
    cout<<a.isConnected();
    vector<Continent*> continents = a.getContinents();
    for(int i = 0; i< continents.size();i++){
        cout<<continents[i]->isConnected();

    }
}