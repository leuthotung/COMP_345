//
// Created by tungleu on 11/17/19.
//

#ifndef COMP345_PLAYERSTRATEGIES_H
#define COMP345_PLAYERSTRATEGIES_H

#include "Player.h"
class PlayerStrategies {
public:
    virtual void reinforce(Player* player)= 0;
    virtual void attack(Player* player)= 0;
    virtual  void fortify(Player* player)= 0;

};
class Human: public PlayerStrategies{
public:
    void reinforce(Player *player);
    void attack(Player* player);
    void fortify(Player* player);
};
class Aggresive: public PlayerStrategies{
public:
    void reinforce(Player *player);
    void attack(Player* player);
    void fortify(Player* player);
};

class Benvolent: public PlayerStrategies{
public:
    void reinforce(Player *player);
    void attack(Player* player);
    void fortify(Player* player);

};

#endif //COMP345_PLAYERSTRATEGIES_H
