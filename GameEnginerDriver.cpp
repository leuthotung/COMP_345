#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include <algorithm>
#include <random>
using namespace std;


int main() {
    GameEngine game = GameEngine();
    game.gameInit(game.getMapFiles("../Maps"));
    //game.chooseMap(game.getMapFiles("../Maps"));
   // game.getMap()->print();
    for(int i = 0; i< game.getMap()->getCountries().size();i++){
        cout<<game.getMap()->getCountries()[i]->getName()<<endl;
    }
    game.gameStartUp();
    vector<Player*> gamePlayers = game.getPlayers();
    for(int i = 0; i < gamePlayers.size();i++){
        cout<<gamePlayers[i]->getName()<<endl;
        cout<<"List of countries"<<endl;
        for(int k = 0; k<gamePlayers[i]->getCountries().size(); k++){
            cout<<gamePlayers[i]->getCountries()[k]->getName()<<endl;
        }
    }
    for(int i = 0; i< game.getMap()->getCountries().size();i++){
        cout<<game.getMap()->getCountries()[i]->getName()<<endl;
    }





}
