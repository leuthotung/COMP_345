#include "Player.h"
#include <string>
using namespace std;

Player::Player(string name) {
    this->name = new string(name);
    this->hand = new Hand();
    this->dice = new Dice();
}

Player::Player() {

}

Player::~Player() {

}

void Player::reinforce() {
    cout<<"Reinforced"<<endl;

}

void Player::attack() {
    cout<<"Attack"<<endl;

}

void Player::fortify() {
    cout<<"Fortified"<<endl;

}

void Player::addCountry(Country* newCountry) {
    countries.push_back(newCountry);
}

Dice *Player::getDice() {
    return this->dice;
}

Hand *Player::getHand() {
    return this->hand;
}


