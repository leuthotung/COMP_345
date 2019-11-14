#include "GameObserver.h"


GameObserver::GameObserver()
{
};

GameObserver::GameObserver(Player* s)
{
	_subject = s;
	_subject->Attach(this);
}

GameObserver::~GameObserver() {
	_subject->Detach(this);
}

void GameObserver::Update() {
	display();
}

void GameObserver::display() {
	cout << "-----------GAMER OBSERVER----------- " << endl;
	cout << "Player: " <<_subject->getName()<< endl;
	cout << "Phase: "<<_subject->getPhase() << endl;
	cout << "Hand: "  ;
	_subject->getHand()->display();
	cout << "ArmyCounter: " << _subject->getHand()->getArmyCounter()+5 << endl;
	cout << "Owned Country: "<<endl;
	_subject->showInformation();
}
