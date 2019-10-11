
#include <iostream>
#include "Cards.h";

using namespace std;

int main()
{

	Hand* hand = new Hand();
	hand->display();
	Deck* myDeck = &Deck(49); 
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
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	myDeck->display();

	return 0;
}
 