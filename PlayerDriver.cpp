/*
//
// Created by tungleu on 10/11/19.
//
#include "MapLoader.h"
#include "Player.h"
#include "GameEngine.h"
int main() {

    Map *map = new Map();
    *map = readMapFile("../Maps/europe.map");
    Player* Tung = new Player("Tung");
    Tung->setMap(map);
    Player* Young = new Player("Young");
    Young->setMap(map);
    Player* Yifan = new Player("Yifan");
    Yifan->setMap(map);
    vector<Player*> players = {Tung, Young, Yifan};
    PhaseObserver* TungPhaseObserver = new PhaseObserver(Tung);
    PhaseObserver* YoungPhaseObserver = new PhaseObserver(Young);
    PhaseObserver* YifanPhaseObserver = new PhaseObserver(Yifan);
    GameStatsObserver* Tung1Observer = new GameStatsObserver(Tung);
    GameStatsObserver* Young1Observer = new GameStatsObserver(Young);
    GameStatsObserver* Yifan1Observer = new GameStatsObserver(Yifan);
    Tung->setPlayers(players);
    Young->setPlayers(players);
    Yifan->setPlayers(players);
    //Add 10 armies to each country
    for(int i = 0; i< map->getCountries().size();i++){
        map->getCountries()[i]->addArmies(10);
    }
    int count = 0;
    //Assign armies
    while(count< map->getCountries().size()){
        for(int i = 0; i< players.size();i++){
            if(count == map->getCountries().size())
                break;
            players[i]->addCountry(map->getCountries()[count]);
            map->getCountries()[count]->setOwner(players[i]);
            count++;
        }
    }
    //infinite loop for demo
    // Deck *deck = new Deck(map->getCountries().size());
    while(true){
        for(int i = 0; i< players.size();i++){
            players[i]->chooseStrategy();
            players[i]->reinforce();
            players[i]->attack();
            players[i]->fortify();
        }
    }






}
*/
