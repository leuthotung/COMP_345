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
    game.gameStartUp2();
    game.gameLoop();





}
