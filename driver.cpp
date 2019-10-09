
#include <iostream>
#include "Cards.h";

using namespace std;

int main()
{

	Hand* hand = new Hand(9, 0, 3);
	while (hand->getTotalCards() >= 5)
		hand->exchange();
	hand->display();
	cout << hand->getArmyCounter() <<endl ;
	hand->~Hand();
	Deck* myDeck = &Deck(50); 
	myDeck->draw().display();
	myDeck->draw().display();
	myDeck->draw().display();
	myDeck->display();
	//The rest is test for draw , no bug when I tested by  manual input deck vector
	//hand->draw();
	//hand->draw();
	//hand->draw();
    //	hand->display();
	//hand->exchange();
	//hand->display();
	//mydeck->display();


	return 0;
}
 