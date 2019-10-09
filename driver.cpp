
#include <iostream>
#include "Cards.h";

using namespace std;

int main()
{

	Hand* hand = new Hand();
	hand->display();
	Deck* myDeck = &Deck(50); 
	myDeck->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	myDeck->display();
	hand->display();

	return 0;
}
 