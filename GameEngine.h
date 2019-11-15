//
// Created by tungleu on 10/27/19.
//

#ifndef COMP345_GAMEENGINE_H
#define COMP345_GAMEENGINE_H

#include "MapLoader.h"
#include "Player.h"
#include "GameObserver.h"
#include <vector>
#include <string>

using namespace std;


class GameEngine {
private:
    Map *gameMap;
    vector<Player*> players;


public:
    GameEngine();
    ~GameEngine();
    vector<string> getMapFiles(string directory);
    Map* getMap();
    vector<Player*> getPlayers();
    void setMap(Map* map);
    void setPlayers(vector<Player*> gamePlayers);
    void gameStartUp2();
    void gameStartUp();
    void gameLoop();
    void gameInit(vector<string> maps);

};


#endif //COMP345_GAMEENGINE_H
