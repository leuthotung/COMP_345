//
// Created by tungleu on 10/11/19.
//
#include "MapLoader.h"
#include "Player.h"
#include "GameObserver.h"
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
	GameStaticsObserver* Tung1Observer = new GameStaticsObserver(Tung);
	GameStaticsObserver* Young1Observer = new GameStaticsObserver(Young);
	GameStaticsObserver* Yifan1Observer = new GameStaticsObserver(Yifan);

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
            players[i]->reinforce();
            players[i]->attack();
            players[i]->fortify();
        }
    }





}
