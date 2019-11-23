//
// Created by tungleu on 11/18/19.
//

#include "GameObservers.h"
#include "Player.h"
#include <iostream>
GameObservers::~GameObservers() {

}

GameObservers::GameObservers() {

}
PhaseObserver::PhaseObserver()
{
};

PhaseObserver::PhaseObserver(Player* s)
{
    _subject = s;
    _subject->Attach(this);
}


PhaseObserver::~PhaseObserver() {
    _subject->Detach(this);
}

void PhaseObserver::Update() {
    display();
}

void PhaseObserver::display() {
    if (_subject->getObserverSelect() !=1) {
        cout << "-----------PHASE OBSERVER----------- " << endl;
        cout << "Player: " <<_subject->getName()<< endl;
        cout << "Phase: "<<_subject->getPhase() << endl;
        cout << "Hand: "  ;
        _subject->getHand()->display();
        cout << "ArmyCounter: " << _subject->getHand()->getArmyCounter()+5 << endl;
        cout << "Owned Country: "<<endl;
        _subject->showInformation();
    }
}
GameStatsObserver::GameStatsObserver()
{
};

GameStatsObserver::GameStatsObserver(Player* s)
{
    _subject = s;
    _subject->Attach(this);
}

GameStatsObserver::~GameStatsObserver() {
    _subject->Detach(this);
}

void GameStatsObserver::Update() {
    display();
}

void GameStatsObserver::display() {
    if (_subject->getObserverSelect() != 0)
    {
        cout << "-----------GAME STATISTICS OBSERVER----------- " << endl;
        cout << "Total Countries: " << _subject->getMap()->getCountries().size() << endl;
        for (int i = 0; i < _subject->getPlayers().size(); i++) {
            cout << _subject->getPlayers()[i]->getName() << " has own " << (float)_subject->getPlayers()[i]->getCountries().size() / _subject->getMap()->getCountries().size() * 100 << " percentage of world" << endl;
            if ((float)_subject->getPlayers()[i]->getCountries().size() / _subject->getMap()->getCountries().size() * 100 == 100) {
                cout << _subject->getPlayers()[i]->getName() << " win the game" << endl;
                exit(0);
            }
        }

        for (int i = 0; i < _subject->getPlayers().size(); i++)
            if (_subject->getPlayers()[i]->getCountries().size() == 0) {
                cout << _subject->getPlayers()[i]->getName() << " has no countries and will be eliminated after atacking phase" << endl;
            }

    }
}