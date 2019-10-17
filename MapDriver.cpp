//
// Created by tungleu on 9/29/19.
//
#include "Map.h"
#include <iostream>
#include <vector>
#include "MapLoader.h"
using namespace std;

/*int main(){
    Map a = readMapFile("../Maps/europe.map");
    //a.print();
    if(a.isConnected()){
        cout<<"The map is a connected graph"<<endl;
        vector<Continent*> continents = a.getContinents();
        for(int i = 0; i< continents.size();i++){

            if(continents[i]->isConnected()){
                cout<<continents[i]->getName()<<" is connected subgraph"<<endl;
            }
            else{
                cout<<continents[i]->getName()<<" is not connected subgraph"<<endl;
            }


        }
    }
    else{
        cout<<"The map is not a connected graph"<<endl;
    }

}*/
