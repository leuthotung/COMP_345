//
// Created by tungleu on 10/27/19.
//

#include "GameEngine.h"
#include <dirent.h>
#include <iostream>
#include <vector>
#include <algorithm>


GameEngine::GameEngine() {

}

GameEngine::~GameEngine() {

}


void GameEngine::gameInit(vector<string> maps) {
    int mapNumber;
    int numberOfPlayers;
    bool valid1 = true;
    bool valid = true;
    //Choose the map
    //For now invalid maps will just result the program to end , will have the plan to handle it later
    while (valid) {

        cout << "Please choose valid map number on this list" << endl;
        for (int i = 0; i < maps.size(); i++)
            cout << i << " " << maps[i] << endl;
        cin >> mapNumber;
        if (mapNumber >= 0 && mapNumber < maps.size()) {
            string directory = "../Maps/" + maps[mapNumber];
            Map *map = new Map();
            *map = readMapFile(directory);
            this->setMap(map);
            valid = false;
            cout << "Map " << maps[mapNumber] << " has been chosen" << endl;

        } else {
            cout << "The number is out of index please choose again" << endl;
        }
    }
    //Choose number of Players
    while (valid1) {
        cout << "Please enter valid number of players (between 2-6)" << endl;
        cin >> numberOfPlayers;
        if (numberOfPlayers >= 2 && numberOfPlayers <= 6)
            valid1 = false;
        else {
            cout << "Invalid number of players! Please choose again (between 2-6)" << endl;
        }
    }
    vector<Player *> gamePlayers;
    //Prompt Players their names
    for (int i = 0; i < numberOfPlayers; i++) {
        string name;
        cout << "Please enter name of player " << i << ": " << endl;
        cin >> name;
        Player *player = new Player(name);
        player->chooseStrategy();
        player->setMap(this->gameMap);
        PhaseObserver *phaseObserver = new PhaseObserver(player);
        GameStatsObserver *gameStaticsObserver = new GameStatsObserver(player);
        gamePlayers.push_back(player);

    }
    this->setPlayers(gamePlayers);
    //Set pointer to players to Player
    for (int i = 0; i < numberOfPlayers; i++) {
        players[i]->setPlayers(players);
    }


}

//Start-up phase
void GameEngine::gameStartUp() {
    //Shuffle the turn
    random_shuffle(players.begin(), players.end());
    int numberOfCountry = gameMap->getCountries().size();
    int count = 0;
    //Assign countries to players
    while (count < numberOfCountry) {
        for (int i = 0; i < players.size(); i++) {
            if (count == numberOfCountry)
                break;
            players[i]->addCountry(gameMap->getCountries()[count]);
            gameMap->getCountries()[count]->setOwner(players[i]);
            count++;
        }
    }
    int numberOfPlayers = players.size();
    int numberOfArmies = 0;
    switch (numberOfPlayers) {
        case 2:
            numberOfArmies = 40;
            break;
        case 3:
            numberOfArmies = 35;
            break;
        case 4:
            numberOfArmies = 30;
            break;
        case 5:
            numberOfArmies = 25;
            break;
        case 6:
            numberOfArmies = 20;
    }

    //Prompt player assign armies on their own country !!
    cout << "EACH PLAYER WILL HAVE " << numberOfArmies << " NUMBER OF ARMIES" << endl;
    int armiesOwned = numberOfArmies;
    while (armiesOwned > 0) {
        for (int i = 0; i < numberOfPlayers; i++) {
            cout << "------------------------" << players[i]->getName() << " TURN ------------------" << endl;
            cout << players[i]->getName() << " has " << armiesOwned << " left" << endl;
            bool indexValid = false;
            int countryIndex;
            while (!indexValid) {
                cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
                for (int j = 0; j < players[i]->getCountries().size(); j++) {
                    cout << "Index " << j << ": Country " << players[i]->getCountries()[j]->getName() << "  Army:"
                         << players[i]->getCountries()[j]->getNumberOfArmies() << endl;
                }
                cout << players[i]->getName() << " Please choose the index of country you want to add armies ";
                cin >> countryIndex;

                if (countryIndex < 0 || countryIndex > players[i]->getCountries().size() - 1) {
                    cout << "Invalid index, please choose again!" << endl;
                } else {
                    players[i]->getCountries()[countryIndex]->addArmies(1);

                    indexValid = true;

                }
            }

        }
        armiesOwned--;
    }


}

//Gaming loop
void GameEngine::gameLoop() {
    cout << "Game start!" << endl;
    bool gameFinish = false;
    while (!gameFinish) {
        for (int i = 0; i < players.size(); i++) {
//          players[i]->chooseStrategy();
            players[i]->reinforce();
            players[i]->attack();
            int temp = players.size();

            //Eliminate losers
            for (int j = 0; j < temp; j++) {
                for (int k = 0; k < players.size(); k++) {
                    if (players[k]->getCountries().size() == 0) {
                        players.erase(players.begin() + k);

                        for (int i = 0; i < players.size(); i++) {
                            players[i]->setPlayers(players);
                        }
                        break;
                    }
                }
            }
            players[i]->fortify();
        }

    }
}


//Get all the map files name in a map directory
vector<string> GameEngine::getMapFiles(string directory) {
    vector<string> files;
    DIR *dirp = opendir(directory.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        string name = dp->d_name;
        if (name != "." && name != "..")
            files.push_back(name);

    }
    closedir(dirp);
    return files;

}

Map *GameEngine::getMap() {
    return this->gameMap;
}

void GameEngine::setMap(Map *map) {
    gameMap = map;
}

void GameEngine::setPlayers(vector<Player *> gamePlayers) {
    players = gamePlayers;
}

vector<Player *> GameEngine::getPlayers() {
    return players;
}

void GameEngine::gameStartUp2() {
    //Shuffle the turn
    random_shuffle(players.begin(), players.end());
    int numberOfCountry = gameMap->getCountries().size();
    int count = 0;
    //Assign countries to players
    while (count < numberOfCountry) {
        for (int i = 0; i < players.size(); i++) {
            if (count == numberOfCountry)
                break;
            players[i]->addCountry(gameMap->getCountries()[count]);
            gameMap->getCountries()[count]->setOwner(players[i]);
            count++;
        }
    }
    int numberOfPlayers = players.size();
    int numberOfArmies = 0;
    switch (numberOfPlayers) {
        case 2:
            numberOfArmies = 40;
            break;
        case 3:
            numberOfArmies = 35;
            break;
        case 4:
            numberOfArmies = 30;
            break;
        case 5:
            numberOfArmies = 25;
            break;
        case 6:
            numberOfArmies = 20;
    }

    //Prompt player assign armies on their own country !! (not round robin)
    cout << "EACH PLAYER WILL HAVE " << numberOfArmies << " NUMBER OF ARMIES" << endl;

    for (int i = 0; i < numberOfPlayers; i++) {
        if (players[i]->getStrategy()->getName() == "Human") {
            cout << "------------------------" << players[i]->getName() << " TURN ------------------" << endl;
            int armiesOwned = numberOfArmies;
            while (armiesOwned > 0) {
                cout << players[i]->getName() << " has " << armiesOwned << " left" << endl;
                bool indexValid = false;
                int countryIndex;
                while (!indexValid) {
                    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
                    for (int j = 0; j < players[i]->getCountries().size(); j++) {
                        cout << "Index " << j << ": Country " << players[i]->getCountries()[j]->getName() << "  Army:"
                             << players[i]->getCountries()[j]->getNumberOfArmies() << endl;
                    }
                    cout << players[i]->getName() << " Please choose the index of country you want to add armies ";
                    cin >> countryIndex;

                    if (countryIndex < 0 || countryIndex > players[i]->getCountries().size() - 1) {
                        cout << "Invalid index, please choose again!" << endl;
                    } else {
                        //This version ask player to fill in armies until it ends, but it wont be round robin fashion..
                        bool validNumber = false;
                        while (!validNumber) {
                            int numberOfArmiesToAdd;
                            cout << "Please choose number of armies you want to add ";
                            cin >> numberOfArmiesToAdd;
                            if (numberOfArmiesToAdd > armiesOwned) {
                                cout << "Please add valid number of armies!! Choose again" << endl;
                            } else {
                                cout << "Added " << numberOfArmiesToAdd << " army to country "
                                     << players[i]->getCountries()[countryIndex]->getName()
                                     << endl;
                                players[i]->getCountries()[countryIndex]->addArmies(numberOfArmiesToAdd);
                                indexValid = true;
                                armiesOwned = armiesOwned - numberOfArmiesToAdd;
                                validNumber = true;
                            }
                        }


                    }
                }
            }
        }
        else{
            cout << "------------------------" << players[i]->getName() << " TURN ------------------" << endl;
            cout << players[i]->getName() << " has " << numberOfArmies << " left" << endl;
            cout << "--------------------ADDING ARMIES AUTOMATICALLY-----------------------" << endl;
            int armyCounter=numberOfArmies;
            int average=numberOfArmies/players[i]->getCountries().size();
            for(int j=0;j<players[i]->getCountries().size()-1;j++){
                players[i]->getCountries()[j]->addArmies(average);
                armyCounter=armyCounter-average;
            }
            players[i]->getCountries()[players[i]->getCountries().size()-1]->addArmies(armyCounter);
            cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
            for (int j = 0; j < players[i]->getCountries().size(); j++) {
                cout << "Index " << j << ": Country " << players[i]->getCountries()[j]->getName() << "  Army:"
                     << players[i]->getCountries()[j]->getNumberOfArmies() << endl;
            }
        }
    }
}




