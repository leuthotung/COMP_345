#include "Player.h"
#include <string>
#include "Map.h"
#include "GameEngine.h"
#include   <windows.h>  

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


using namespace std;

Observer::Observer() {
};
Observer::~Observer() {
};


Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};

void Subject::Notify() {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();
};

Player::Player(string name) {
    this->name = new string(name);
    this->hand = new Hand();
    this->dice = new Dice();
	this->phase = new string("null");
	this->observerSelect = new int(2);
}

Player::Player() {

}

Player::~Player() {

}

Map *Player::getMap() {
    return gameMap;
}

void Player::setMap(Map *map) {
    gameMap = map;
}

vector<Player*> Player::getPlayers()
{
	return players;
}

void Player::setPlayers(vector<Player*> player)
{
	players = player;
}


void Player::addCountry(Country* newCountry) {
    countries.push_back(newCountry);
    newCountry->setOwner(this);
}

void Player::removeCountry(Country *country) {
    for (int i = 0; i < countries.size(); i++)
    {
        if (countries.at(i)->getName() == country->getName())
        {
            countries.erase(countries.begin() + i);
            break;
        }
    }
    cout << *name << " just lost this Country " << country->getName() << endl;

}

int Player::getObserverSelect()
{
	return *observerSelect;
}

Dice *Player::getDice() {
    return this->dice;
}

Hand *Player::getHand() {
    return this->hand;
}

string Player::getName() {
    return *name;
}

string Player::getPhase() {
	return *phase;
}

vector<Country*> Player::getCountries(){
    return countries;
}
// This method show current information of the countries this Player owns
void Player::showInformation() {
    for (int i = 0; i < countries.size(); i++) {
        cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getNumberOfArmies() << endl;
    }
}
//This method checks if player has ownership of the continent
bool Player::hasOwnership(Continent* continent) {
    int countryCounter = 0;
    for(int i = 0; i< this->countries.size(); i++){
        if(countries[i]->getContinent() == continent)
            countryCounter++;
    }
    return(countryCounter == continent->getCountries().size());
}
//This method returns number of armies that Player can have from occupying continents
int Player::armiesFromContinent() {
    int armiesToAdd = 0;
    vector<Continent*> continents=  this->getMap()->getContinents();
    for(int i = 0; i < continents.size(); i++){
        if(this->hasOwnership(continents[i])){
            armiesToAdd += continents[i]->getValue();
            cout<<continents[i]->getValue()<<" armies added since "<< this->getName() <<" owns this Continent: "<<continents[i]->getName()<<endl;
        }
    }
    return armiesToAdd;

}
void Player::reinforce() {
    int armyCounter = 0;
    bool exchangeFlag = false;
	bool nextPhaseFlag = false;
	*phase = "Reinforce";
	system(CLEAR);
	*observerSelect = 2;
	Notify();
    int armiesFromNumberOfCountries = this->countries.size()/3;
    //cout<< this->getName() << " has " << armiesFromNumberOfCountries <<" armies for occupying "<< countries.size()<< " countries"<<endl;
    armyCounter += armiesFromNumberOfCountries;
    armyCounter += this->armiesFromContinent();

    cout << "Do you want to exchange card??(intput 0(false) or 1(true))" << endl;
    while(true){
        if (cin >> exchangeFlag)
            break;
        else {
            cout << "invalid input" << endl;
            cin.clear();
            cin.ignore();
        }
    }
    if (exchangeFlag) {
        armyCounter += this->hand->exchange();
    }

    cout << this->getName() << " will have " <<  armyCounter << " armies  in this reinforcement stage"<<endl;

    while(armyCounter>0) {
        bool indexValid = false;
        int countryIndex;
        cout << "You have  " << armyCounter << " armies left" << endl;
        while (!indexValid) {

            cout << this->getName() << " Please choose the index of country you want to add armies"
                 << endl;
            cin >> countryIndex;

            if (countryIndex < 0 || countryIndex > this->getCountries().size() - 1) {
                cout << "Invalid index, please choose again!" << endl;
            } else {
                bool validNumber = false;
                while (!validNumber) {
                    int numberOfArmiesToAdd;
                    cout << "Please choose number of armies you want to add ";
                    cin >> numberOfArmiesToAdd;
                    if (numberOfArmiesToAdd > armyCounter|| numberOfArmiesToAdd <0) {
                        cout << "Please add valid number of armies!! Choose again" << endl;
                    } else {
                        cout << "Added " << numberOfArmiesToAdd << " army to country "
                             << this->getCountries()[countryIndex]->getName()
                             << endl;
                        this->getCountries()[countryIndex]->addArmies(numberOfArmiesToAdd);
                        indexValid = true;
                        armyCounter = armyCounter - numberOfArmiesToAdd;
                        validNumber = true;
						*observerSelect = 0;
						Notify();
                    }
                }
            }
        }
    }
    cout << "ALL ARMIES ARE PLACED SUCCESSFULLY" << endl;
	while (true) {
		cout << "Do you want to end this phase and start attack phase? input 0(false) or 1(true)" << endl;
		while (true) {
			if (cin >> nextPhaseFlag)
				break;
			else {
				cout << "invalid input" << endl;
				cin.clear();
				cin.ignore();
			}
		}
		if (nextPhaseFlag == true)
		{
			system(CLEAR);
			break;	
		}
		else
			cout << "ALL ARMIES ARE PLACED SUCCESSFULLY, NOTHING TO DO IN REINFORCE PHASE" << endl;
	}

}

void Player::attack() {
    bool attackFlag = false;
    bool continueFlag = false;
    int sourceCountryIndex = 0;
    int targetCountryIndex = 0;
	int changeArmy = 0;
    int winCounter=0;
    int loseCounter = 0;
	
	*observerSelect = 1;
	Notify();
	
    cout << "Do you want to attack? (intput 0(false) or 1(true) )" << endl;
    while (true) {
        if (cin >> attackFlag)
            break;
        else {
            cout << "invalid input" << endl;
            cin.clear();
            cin.ignore();
        }
    }

    while(attackFlag){
		*observerSelect = 0;
		Notify();
        cout << "Choose the index of SOURCE country " << endl;
        while (true) {
            cin >> sourceCountryIndex;
            if (sourceCountryIndex<0 || sourceCountryIndex>countries.size() - 1 || countries[sourceCountryIndex]->getNumberOfArmies() < 2)
                cout << "Invalid input,please input valid index of source country who have enough armies(>=2)" << endl;
            else
                break;
        }
        cout << "--------------This is neighbors information of the source country-----------------" << endl;
        for (int i = 0; i < countries[sourceCountryIndex]->getNeigbors().size(); i++) {
            cout << "Index" << i << " Country:" << countries[sourceCountryIndex]->getNeigbors().at(i)->getName() << "  Army:" << countries[sourceCountryIndex]->getNeigbors().at(i)->getNumberOfArmies() <<
                 "  Owner: " << countries[sourceCountryIndex]->getNeigbors().at(i)->getOwner()->getName() << endl;
        }
        cout << "Choose the index of TARGET country " << endl;
        while (true) {
            cin >> targetCountryIndex;
            if (targetCountryIndex<0 || targetCountryIndex>countries[sourceCountryIndex]->getNeigbors().size() - 1) {
                cout << "Invalid input" << endl;
            }
            else if (countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getName().compare(*name) == 0) {
                cout << "Invalid input, please choose enemy country" << endl;
            }
            else
                break;
        }
        while(true) {
            cout << "There are " << countries[sourceCountryIndex]->getNumberOfArmies() << " in attacking country"
                 << endl;
            cout << "There are "
                 << countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies()
                 << " in defending country" << endl;
            if (countries[sourceCountryIndex]->getNumberOfArmies() == 1) {
                cout << "There is only 1 army left in attacking country" << endl;
                break;
            }
            if (countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() == 0) {
                cout << "There is no army left in defending country" << endl;
                countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->removeCountry(
                        countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
                this->addCountry(countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
				*observerSelect = 1;
				Notify();
				cout << "please move a number of armies from the attacking country to the attacked country,in the range [1 to " << countries[sourceCountryIndex]->getNumberOfArmies() - 1 << "]" << endl;
				while (true) {
					cin >> changeArmy;
					if (changeArmy <= 0 || changeArmy > countries[sourceCountryIndex]->getNumberOfArmies() - 1)
						cout << "invalid input,X must be in the range [1 to " << countries[sourceCountryIndex]->getNumberOfArmies() - 1 << "]" << endl;
					else
						break;
				}
				countries[sourceCountryIndex]->addArmies(-changeArmy);
				countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(changeArmy);
				this->getHand()->draw(gameMap->getDeck());
				break;
			}
            
            
            cout << "Do you want to continue attack current country?(intput 0(false) or 1(true))" << endl;
            while (true) {
                if (cin >> continueFlag)
                    break;
                else {
                    cout << "invalid input" << endl;
                    cin.clear();
                    cin.ignore();
                }
            }
            if (!continueFlag)
                break;
            int numberOfAttackerDices = 0, numberOfDefenderDices = 0;
            cout << "ATTACKER TURN TO CHOOSE NUMBER OF DICE" << endl;
            while (true) {
                if (countries[sourceCountryIndex]->getNumberOfArmies() >= 4) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and 3 " << endl;
                    cin >> numberOfAttackerDices;
                    if (numberOfAttackerDices < 1 || numberOfAttackerDices > 3) {
                        cout << "Invalid number! Please try again." << endl;
                    } else {
                        break;
                    }
                } else if (countries[sourceCountryIndex]->getNumberOfArmies() < 4 &&
                           countries[sourceCountryIndex]->getNumberOfArmies() > 1) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and "
                         << countries[sourceCountryIndex]->getNumberOfArmies() - 1 << endl;
                    cin >> numberOfAttackerDices;
                    if (numberOfAttackerDices < 1 || numberOfAttackerDices > countries[sourceCountryIndex]->getNumberOfArmies() - 1) {
                        cout << "Invalid number! Please try again." << endl;
                    } else {
                        break;
                    }
                }
            }
            dice->roll(numberOfAttackerDices);
            cout << "DEFENDER TURN TO CHOOSE NUMBER OF DICE" << endl;
            while (true)
            {
                winCounter = 0;
                loseCounter = 0;
                if (countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() >= 2) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and 2 " << endl;
                    cin >> numberOfDefenderDices;
                    if (numberOfDefenderDices < 1 || numberOfDefenderDices > 2)
                    {
                        cout << "Invalid number! Please try again." << endl;
                    }
                    else
                    {
                        break;
                    }
                }
                else if (countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() == 1) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and " << countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() << endl;
                    cin >> numberOfDefenderDices;
                    if (numberOfDefenderDices != 1)
                    {
                        cout << "Invalid number! Please try again." << endl;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                    break;
            }
            countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->roll(numberOfDefenderDices);
            cout << "Your dice value:" << endl;
            for (int i = 0; i < dice->get_value().size(); i++) {
                cout << *dice->get_value()[i] << " ";
            }
            cout << endl;
            cout << "Defender dice value:" << endl;
            for (int i = 0; i < countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->get_value().size(); i++) {
                cout << *(countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->get_value()[i]) << " ";
            }
            cout << endl;
            int loop = numberOfAttackerDices< numberOfDefenderDices ? numberOfAttackerDices: numberOfDefenderDices;
            for (int i = 0; i < loop; i++) {
                if (*dice->get_value()[i] > * (countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->get_value()[i]))
                    winCounter++;
                else
                    loseCounter++;
            }
            countries[sourceCountryIndex]->addArmies(-loseCounter);
            countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(-winCounter);
            }
            cout << "Do you want to attack again ?(intput 0(false) or 1(true))" << endl;
            while (true) {
                if (cin >> attackFlag)
                    break;
                else {
                    cout << "invalid input" << endl;
                    cin.clear();
                    cin.ignore();
                }
            }
            if (!attackFlag)
                break;
    }

		system(CLEAR);



}

void Player::fortify() {
    bool fortifyFlag = false;
	bool nextPhaseFlag = false;
    int sourceCountryIndex = 0;
    int targetCountryIndex = 0;
    int changeArmy = 0;
	*observerSelect = 2;
	Notify();
    cout << "Do you want to fortify? (intput 0(false) or 1(true) )" << endl;
    while (true) {
        if (cin >> fortifyFlag)
            break;
        else {
            cout << "invalid input" << endl;
            cin.clear();
            cin.ignore();
        }
    }
    if (fortifyFlag) {
        cout<<"Choose the index of SOURCE country "<<endl;
        while (true) {
            cin >> sourceCountryIndex;
            if (sourceCountryIndex<0 || sourceCountryIndex>countries.size() - 1|| countries[sourceCountryIndex]->getNumberOfArmies() <2)
                cout << "Invalid input,please input valid index of source country which have enough armies(>=2)" << endl;
            else
                break;
        }
        cout << "This is the neighbor information of the source country" << endl;

        for (int i = 0; i < countries[sourceCountryIndex]->getNeigbors().size(); i++) {
            cout << "Index " << i <<
                    " Country:" << countries[sourceCountryIndex]->getNeigbors().at(i)->getName()<<
                    "  Army:" << countries[sourceCountryIndex]->getNeigbors().at(i)->getNumberOfArmies() <<
                    "  Owner: "<<countries[sourceCountryIndex]->getNeigbors().at(i)->getOwner()->getName()<<endl;
        }
        cout << "Choose the index of TARGET country " << endl;
        while (true) {
            cin >> targetCountryIndex;
            if (targetCountryIndex<0 || targetCountryIndex>countries[sourceCountryIndex]->getNeigbors().size() - 1)
                cout << "invalid input" << endl;
            else if ((countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getName().compare(this->getName()) != 0))
                cout<< "PLEASE CHOOSE THE COUNTRY YOU OWN !!"<<endl;
            else
                break;
        }
        cout << "Choose the numbers of armies you want to move" << endl;
        while (true) {
            cin >> changeArmy;
            if (changeArmy<=0 || changeArmy> countries[sourceCountryIndex]->getNumberOfArmies()-1)
                cout << "Invalid input,X must be in the range [1 to(number of armies on the source country - 1)]" << endl;
            else
                break;
        }
        countries[sourceCountryIndex]->addArmies(-changeArmy);
        countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(changeArmy);
		*observerSelect = 0;
		Notify();
		while (true) {
			cout << "Do you want to end this phase? input 0(false) or 1(true)" << endl;
			while (true) {
				if (cin >> nextPhaseFlag)
					break;
				else {
					cout << "invalid input" << endl;
					cin.clear();
					cin.ignore();
				}
			}
			if (nextPhaseFlag == true)
			{
				system(CLEAR);
				break;
			}
			else
				cout << "PLEASE END YOUR PHASE AFTER CHECKING YOUR INFORMATION" << endl;
		}
    }
    else {
		system(CLEAR);

    }


}











