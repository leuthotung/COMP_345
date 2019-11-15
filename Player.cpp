#include "Player.h"
#include <string>
using namespace std;

Player::Player(string name) {
    this->name = new string(name);
    this->hand = new Hand();
    this->dice = new Dice();
	this->armyCounter = new int(0);
	this->asiaCounter = new int(0);
	this->euCounter = new int(0);
	this->naCounter = new int(0);
	this->saCounter = new int(0);
	this->africaCounter = new int(0);
	this->oceaniaCounter = new int(0);
}

Player::Player() {

}

Player::~Player() {

}

void Player::reinforce() {
	//cout.setf(std::ios_base::boolalpha);
	//cin.setf(std::ios_base::boolalpha);
	bool exchangeFlag = false;
	int countryIndex = 0;
	int addArmy = 0;
	cout << "------------------REINFORCE PHASE START-------------------------" << endl;
	*armyCounter += this->countries.size() / 3;
	*armyCounter += continentCheck();
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
	
	if (exchangeFlag == true)
		* armyCounter += this->hand->exchange();
	cout << "will get " << *armyCounter << " armies  in reinforce stage"<<endl;
	cout << "--------------------This is your information-----------------------" << endl;
	for (int i = 0; i < countries.size(); i++) {
		cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getArmies() << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
	while (*armyCounter > 0)
	{
		countryIndex = 0;
		addArmy = 0;
		cout << "there are " << *armyCounter << " armies need to be place"<<endl;
		cout << "Choose the index of country you want to change"<<endl;
		cin >> countryIndex;
		if (countryIndex<0 || countryIndex>countries.size() - 1)
		{
			cout << "invalid input" << endl;
			continue;
		}
		cout << "Choose the number of armies you want to place"<<endl;
		cin >> addArmy;
		if (addArmy < 0 || *armyCounter - addArmy < 0)
		{
			cout << "invalid input" << endl;
			continue;
		}
		countries[countryIndex]->addArmy(addArmy);
		*armyCounter -= addArmy;
	}
	cout << "all armies are placed successfully" << endl; 
	cout << "--------------------This is your information-----------------------" << endl;
	for (int i = 0; i < countries.size(); i++) {
		cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getArmies() << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
	cout << "--------------------REINFORCE PHASE END--------------------------" << endl;
}

void Player::attack() {
<<<<<<< Updated upstream
    cout<<"Attack"<<endl;
=======
    bool attackFlag = false;
    bool continueFlag = false;
    int sourceCountryIndex = 0;
    int targetCountryIndex = 0;
	int changeArmy = 0;
    int winCounter=0;
    int loseCounter = 0;
	
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
			//	if (countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getCountries().size() == 1)
				//	cout << countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getName()<<" will lose and be eminated" << endl;
                countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->removeCountry(
                        countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
                this->addCountry(countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
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

		system("CLS");


>>>>>>> Stashed changes

}

void Player::fortify() {
	bool fortifyFlag = false;
	int sourceCountryIndex = 0;
	int targetCountryIndex = 0;
	int changeArmy = 0;
	cout << "--------------------FORTIFICATION PHASE START--------------------------" << endl;
	cout << "do you want to fortify? (intput 0(false) or 1(true) )" << endl;
	while (true) {
		if (cin >> fortifyFlag)
			break;
		else {
			cout << "invalid input" << endl;
			cin.clear();
			cin.ignore();
		}
	}
	if (fortifyFlag == true) {
		cout << "--------------------This is your information-----------------------" << endl;
		for (int i = 0; i < countries.size(); i++) {
			cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getArmies() << endl;
		}
		cout << "----------------------------------------------------------------------" << endl;
		cout<<"Choose the index of SOURCE country "<<endl;
		while (true) {
			cin >> sourceCountryIndex;
			if (sourceCountryIndex<0 || sourceCountryIndex>countries.size() - 1|| countries[sourceCountryIndex]->getArmies() <2)
				cout << "invalid input,please input valid index of source country who have enough armies(>=2)" << endl;
			else
				break;
		}
		cout << "This is the neighbor information of the source country" << endl;
		for (int i = 0; i < countries[sourceCountryIndex]->getNeigbors().size(); i++) {
			cout << "Index" << i << " Country:" << countries[sourceCountryIndex]->getNeigbors().at(i)->getName()<< "  Army:" << countries[sourceCountryIndex]->getNeigbors().at(i)->getArmies() << endl;
		}
		cout << "Choose the index of TARGET country " << endl;
		while (true) {
			cin >> targetCountryIndex;
			if (targetCountryIndex<0 || targetCountryIndex>countries[sourceCountryIndex]->getNeigbors().size() - 1 )
				cout << "invalid input" << endl;
			else
				break;
		}
		cout << "Choose the numbers of armies you want to move" << endl;
		while (true) {
			cin >> changeArmy;
			if (changeArmy<=0 || changeArmy> countries[sourceCountryIndex]->getArmies()-1)
				cout << "invalid input,X must be in the range [1 to(number of armies on the source country - 1)]" << endl;
			else
				break;
		}
		countries[sourceCountryIndex]->addArmy(-changeArmy);
		countries[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmy(changeArmy);
		cout << "--------------------This is your information-----------------------" << endl;
		for (int i = 0; i < countries.size(); i++) {
			cout << "Index" << i << " Country:" << countries[i]->getName() << "  Army:" << countries[i]->getArmies() << endl;
		}
		cout << "----------------------------------------------------------------------" << endl;
		cout << "--------------------FORTIFICATION PHASE END--------------------------" << endl;
	}
	else {
		cout << "--------------------FORTIFICATION PHASE END--------------------------" << endl;
		return;
	}
	

}

int Player::continentCheck()
{
	int tempCounter = 0;
	if (*asiaCounter == 5) //5 means 5 countries in asia
		tempCounter += 3; // control value
	if (*euCounter == 6)
		tempCounter += 3; // control value
	if (*saCounter == 7)
		tempCounter += 3; // control value
	if (*naCounter == 2)
		tempCounter += 3; // control value
	if (*africaCounter == 9)
		tempCounter += 3; // control value
	if (*oceaniaCounter == 10)
		tempCounter += 3; // control value
	return tempCounter;
}

void Player::addCountry(Country* newCountry) {
    countries.push_back(newCountry);
	if (newCountry->getContinent().getName().compare("asia") == 0) {
		++*asiaCounter;
	}
	else if (newCountry->getContinent().getName().compare("europe") == 0)
		++*euCounter;
	else if (newCountry->getContinent().getName().compare("northAmerica") == 0)
		++*naCounter;
	else if (newCountry->getContinent().getName().compare("southAmerica") == 0)
		++*saCounter;
	else if (newCountry->getContinent().getName().compare("africa") == 0)
		++*africaCounter;
	else if (newCountry->getContinent().getName().compare("oceania") == 0)
		++*oceaniaCounter;
}

Dice *Player::getDice() {
    return this->dice;
}

Hand *Player::getHand() {
    return this->hand;
}


