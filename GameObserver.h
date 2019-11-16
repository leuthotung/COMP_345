#pragma once

#include "Player.h"

class PhaseObserver:public Observer {
public:
	PhaseObserver();	
	PhaseObserver(Player* s);
	~PhaseObserver();
	void Update();
	void display();
private:
	Player* _subject;
	
};

class GameStaticsObserver :public Observer {
public:
	GameStaticsObserver();
	GameStaticsObserver(Player* s);
	~GameStaticsObserver();
	void Update();
	void display();
private:
	Player* _subject;

};