#pragma once

#include "Observer.h"
#include "Player.h"


class GameObserver:public Observer {
public:
	GameObserver();	
	GameObserver(Player* s);
	~GameObserver();
	void Update();
	void display();
private:
	Player* _subject;
	
};