#include "GameObserver.h"


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
	cout << "-----------PHASE OBSERVER----------- " << endl;
	cout << "Player: " <<_subject->getName()<< endl;
	cout << "Phase: "<<_subject->getPhase() << endl;
	cout << "Hand: "  ;
	_subject->getHand()->display();
	cout << "ArmyCounter: " << _subject->getHand()->getArmyCounter()+5 << endl;
	cout << "Owned Country: "<<endl;
	_subject->showInformation();
}


GameStaticsObserver::GameStaticsObserver()
{
};

GameStaticsObserver::GameStaticsObserver(Player* s)
{
	_subject = s;
	_subject->Attach(this);
}

GameStaticsObserver::~GameStaticsObserver() {
	_subject->Detach(this);
}

void GameStaticsObserver::Update() {
	display();
}

void GameStaticsObserver::display() {
	cout << "-----------GAME STATICS OBSERVER----------- " << endl;
	cout <<"Total Countries: "<< _subject->getMap()->getCountries().size() << endl;
	cout << "" << endl;
}
