//
// Created by tungleu on 11/18/19.
//

#ifndef COMP345_GAMEOBSERVERS_H
#define COMP345_GAMEOBSERVERS_H

#include "Player.h"


class GameObservers {
public:
    ~GameObservers();
    virtual void Update() = 0;
protected:
    GameObservers();
};

class PhaseObserver:public GameObservers {
public:
    PhaseObserver();
    PhaseObserver(Player* s);
    ~PhaseObserver();
    void Update();
    void display();
private:
    Player* _subject;

};
class GameStatsObserver :public GameObservers {
public:
    GameStatsObserver();
    GameStatsObserver(Player* s);
    ~GameStatsObserver();
    void Update();
    void display();
private:
    Player* _subject;

};


#endif //COMP345_GAMEOBSERVERS_H
