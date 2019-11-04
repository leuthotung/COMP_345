#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include <algorithm>
#include <random>
using namespace std;
bool IsSubset(std::vector<int> A, std::vector<int> B)
{
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}

int main() {
    /*GameEngine game = GameEngine();
    game.gameInit(game.getMapFiles("../Maps"));
    //game.chooseMap(game.getMapFiles("../Maps"));
   // game.getMap()->print();
    *//*for(int i = 0; i< game.getMap()->getCountries().size();i++){
        cout<<game.getMap()->getCountries()[i]->getName()<<endl;
    }*//*
    game.gameStartUp();*/
    /*vector<Player*> gamePlayers = game.getPlayers();
    for(int i = 0; i < gamePlayers.size();i++){
        cout<<gamePlayers[i]->getName()<<endl;
        cout<<"List of countries"<<endl;
        for(int k = 0; k<gamePlayers[i]->getCountries().size(); k++){
            cout<<gamePlayers[i]->getCountries()[k]->getName()<<endl;
        }
    }*/
    /*for(int i = 0; i< game.getMap()->getCountries().size();i++){
        cout<<game.getMap()->getCountries()[i]->getName()<<endl;
    }*/

vector<int> A = {5,3,4,6};
vector<int> B = {3,4,5,6,7,8,9,0,1};

cout<< IsSubset(B,A)<<endl;




}
