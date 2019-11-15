//
// Created by tungleu on 10/11/19.
//
#include "MapLoader.h"
#include "Player.h"


<<<<<<< Updated upstream
int main(){
  Player* Lebron =  new Player("Lebron");
  Country* Canada = new Country("Canada",new Continent("northAmerica"));
	Country* USA = new Country("USA", new Continent("northAmerica"));
	Country* China = new Country("China", new Continent("asia"));
  Country* Japan = new Country("Japan", new Continent("asia"));
	Country* Korea = new Country("Korea", new Continent("asia"));
  Country* India = new Country("India", new Continent("asia"));
  Country* Vietnam = new Country("Vietnam", new Continent("asia")); 
	USA->addNeighbor(Canada);
	Canada->addNeighbor(USA);
	China->addNeighbor(Japan);
	China->addNeighbor(Korea);
	Japan->addNeighbor(Korea);
	Japan->addNeighbor(China);
	Korea->addNeighbor(China);
	Korea->addNeighbor(Japan);
	India->addNeighbor(Vietnam);
	Vietnam->addNeighbor(India);
	cout<<USA->getNeigbors().at(0)->getName()<<endl;
	cout << Japan->getArmies()<< endl;
	cout<<Japan->getContinent().getName()<<endl;
  Lebron->addCountry(Canada);
	Lebron->addCountry(USA);
	Lebron->addCountry(China);
  Lebron->addCountry(Japan);
	Lebron->addCountry(Korea);
	Lebron->addCountry(India);
	Lebron->addCountry(Vietnam);
	Deck* myDeck = new Deck(49);
	//cout <<Lebron->continentCheck()<< endl;
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->draw(myDeck);
	Lebron->getHand()->display();
	Lebron->reinforce();
	Lebron->attack();
	Lebron->fortify();
=======
    Map *map = new Map();
    *map = readMapFile("../Maps/europe.map");
    Player* Tung = new Player("Tung");
    Tung->setMap(map);
    Player* Young = new Player("Young");
    Young->setMap(map);
    Player* Yifan = new Player("Yifan");
    Yifan->setMap(map);
    vector<Player*> players = {Tung, Young, Yifan};
	PhaseObserver* TungPhaseObserver = new PhaseObserver(Tung);
	PhaseObserver* YoungPhaseObserver = new PhaseObserver(Young);
	PhaseObserver* YifanPhaseObserver = new PhaseObserver(Yifan);
	GameStaticsObserver* Tung1Observer = new GameStaticsObserver(Tung);
	GameStaticsObserver* Young1Observer = new GameStaticsObserver(Young);
	GameStaticsObserver* Yifan1Observer = new GameStaticsObserver(Yifan);

    //Add 10 armies to each country
    for(int i = 0; i< map->getCountries().size();i++){
        map->getCountries()[i]->addArmies(10);
    }
    int count = 0;
    //Assign armies
    while(count< map->getCountries().size()){
        for(int i = 0; i< players.size();i++){
            if(count == map->getCountries().size())
                break;
            players[i]->addCountry(map->getCountries()[count]);
            map->getCountries()[count]->setOwner(players[i]);
            count++;
        }
    }
    //infinite loop for demo
   // Deck *deck = new Deck(map->getCountries().size());
    while(true){
        for(int i = 0; i< players.size();i++){
            players[i]->reinforce();
            players[i]->attack();
            players[i]->fortify();
        }
    }
>>>>>>> Stashed changes

    
   // Lebron->getDice()->roll();

}*/
