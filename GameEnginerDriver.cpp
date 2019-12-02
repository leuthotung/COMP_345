#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>
#include "GameEngine.h"
#include <algorithm>
#include <random>
using namespace std;


int main() {
    int number;
    GameEngine game = GameEngine();
    cout<<"Please choose game mode "<<endl;
    cout<<"0 Single Game Mode"<<endl;
    cout<<"1 Tournament Game Mode"<<endl;
    while(true) {
        cin >> number;
        if (number == 0) {
            cout << "SINGLE GAME MODE SELECTED" << endl;
            game.singleGame();
            break;
        } else if (number == 1) {
            cout << "TOURNAMENT GAME MODE SELECTED" << endl;
            game.tournamentGame();
            break;
        } else {
            cout << "Invalid number please try again " << endl;
        }
    }





}
