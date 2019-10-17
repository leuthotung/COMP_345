
#include <iostream>
#include "Cards.h";

using namespace std;

int main()
{
	Hand* hand = new Hand();
	hand->display();
	Deck* myDeck = &Deck(49); 
	myDeck->display();
	hand->draw(myDeck);//draw from myDeck 
	hand->display();
	hand->draw(myDeck); 
	hand->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->display();
	hand->draw(myDeck);
	hand->displayCurrentCard();//display current Card objects 
	hand->display();//display current numbers of cards
	hand->draw(myDeck);//there are 5 cards,so it will exchange automatically
	hand->exchange();//now there are 2 card, won't exchange
	hand->display();
	hand->draw(myDeck);//4
	hand->display();
	hand->draw(myDeck);//5
	hand->display();
	hand->exchange();//try to exchange manually
	hand->display();
	myDeck->display();
	/*
	Hand* hand2 = new Hand();
	hand2->draw(myDeck);
	hand2->draw(myDeck);
	hand2->display();
	myDeck->display();
	*/

	return 0;
}
 