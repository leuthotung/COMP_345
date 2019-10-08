
#include <iostream>
#include "Cards.h";

using namespace std;
int main()
{
	Card* a = &Card(INFANTRY);
	a->display();
	Hand* hand = &Hand(9, 0, 3);
	while (hand->getTotalCards() >= 5)
		hand->exchange();
	hand->display();
	cout << hand->getArmyCounter() <<endl ;
	Deck* myDeck = &Deck(50);
	myDeck->getDECKDATA();//at this step all the deck vector data is lost 

	//The rest is test for draw , no bug when I tested by  manual input deck vector
	//hand->draw();
	//hand->draw();
	//hand->draw();
    //	hand->display();
	//hand->exchange();
	//hand->display();
	//mydeck->display();  
}
 