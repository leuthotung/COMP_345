//
// Created by tungleu on 11/17/19.
//

#ifndef COMP345_PLAYERSTRATEGIES_H
#define COMP345_PLAYERSTRATEGIES_H

#include "Player.h"

class Player;

class PlayerStrategies {
private:
    string name;
public:
    virtual string getName()=0;
    virtual void reinforce(Player *player) = 0;
    virtual void attack(Player *player) = 0;
    virtual void fortify(Player *player) = 0;
};

class Human : public PlayerStrategies {
private:
    const string name="Human";
public:
    string getName(){return name;}
    void reinforce(Player *player);
    void attack(Player *player);
    void fortify(Player *player);
};

class Aggressive : public PlayerStrategies {
private:
    const string name="Aggressive";
public:
    string getName(){return name;}
    void reinforce(Player *player);
    void attack(Player *player);
    void fortify(Player *player);
};

class Benevolent : public PlayerStrategies {
private:
    const string name="Benevolent";
public:
    string getName(){return name;}
    void reinforce(Player *player);
    void attack(Player *player);
    void fortify(Player *player);
};

class Random : public PlayerStrategies {
private:
    const string name="Random";
public:
    string getName(){return name;}
    void reinforce(Player *player);
    void attack(Player *player);
    void fortify(Player *player);
};

class Cheater : public PlayerStrategies {
private:
    const string name="Cheater";
public:
    string getName(){return name;}
    void reinforce(Player *player);
    void attack(Player *player);
    void fortify(Player *player);
};

#endif //COMP345_PLAYERSTRATEGIES_H
