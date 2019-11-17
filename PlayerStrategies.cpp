//
// Created by tungleu on 11/17/19.
//

#include "PlayerStrategies.h"

void Human::reinforce(Player* player) {
    int armyCounter = 0;
    bool exchangeFlag = false;
    cout << "------------------REINFORCE PHASE START-------------------------" << endl;
    int armiesFromNumberOfCountries = player->getCountries().size()/3;
    cout<< player->getName() << " has " << armiesFromNumberOfCountries <<" armies for occupying "<< player->getCountries().size()<< " countries"<<endl;
    armyCounter += armiesFromNumberOfCountries;
    armyCounter += player->armiesFromContinent();
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
        armyCounter += player->getHand()->exchange();
    }

    cout << player->getName() << " will have " <<  armyCounter << " armies  in this reinforcement stage"<<endl;

    while(armyCounter>0) {
        bool indexValid = false;
        int countryIndex;
        cout << "You have  " << armyCounter << " armies left" << endl;
        while (!indexValid) {

            cout << player->getName() << " Please choose the index of country you want to add armies"
                 << endl;
            player->showInformation();
            cin >> countryIndex;

            if (countryIndex < 0 || countryIndex > player->getCountries().size() - 1) {
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
                             << player->getCountries()[countryIndex]->getName()
                             << endl;
                        player->getCountries()[countryIndex]->addArmies(numberOfArmiesToAdd);
                        indexValid = true;
                        armyCounter = armyCounter - numberOfArmiesToAdd;
                        validNumber = true;
                    }
                }
            }
        }
    }
    cout << "ALL ARMIES ARE PLACED SUCCESSFULLY" << endl;
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "--------------------REINFORCE PHASE END--------------------------" << endl;


}

void Human::attack(Player *player) {
    bool attackFlag = false;
    bool continueFlag = false;
    int sourceCountryIndex = 0;
    int targetCountryIndex = 0;
    int winCounter=0;
    int loseCounter = 0;
    cout << "--------------------ATTACK PHASE START--------------------------" << endl;
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
        cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
        player->showInformation();
        cout << "----------------------------------------------------------------------" << endl;
        cout << "Choose the index of SOURCE country " << endl;
        while (true) {
            cin >> sourceCountryIndex;
            if (sourceCountryIndex<0 || sourceCountryIndex> player->getCountries().size() - 1 || player->getCountries()[sourceCountryIndex]->getNumberOfArmies() < 2)
                cout << "Invalid input,please input valid index of source country who have enough armies(>=2)" << endl;
            else
                break;
        }
        cout << "--------------This is neighbors information of the source country-----------------" << endl;
        for (int i = 0; i < player->getCountries()[sourceCountryIndex]->getNeigbors().size(); i++) {
            cout << "Index" << i << " Country:" << player->getCountries()[sourceCountryIndex][sourceCountryIndex].getNeigbors().at(i)->getName() << "  Army:" << player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getNumberOfArmies() <<
                 "  Owner: " << player->getCountries()[sourceCountryIndex][sourceCountryIndex].getNeigbors().at(i)->getOwner()->getName() << endl;
        }
        cout << "Choose the index of TARGET country " << endl;
        while (true) {
            cin >> targetCountryIndex;
            if (targetCountryIndex<0 || targetCountryIndex>player->getCountries()[sourceCountryIndex]->getNeigbors().size() - 1) {
                cout << "Invalid input" << endl;
            }
            else if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getName().compare(player->getName()) == 0) {
                cout << "Invalid input, please choose enemy country" << endl;
            }
            else
                break;
        }
        while(true) {
            cout << "There are " << player->getCountries()[sourceCountryIndex]->getNumberOfArmies() << " in attacking country"
                 << endl;
            cout << "There are "
                 << player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies()
                 << " in defending country" << endl;
            if (player->getCountries()[sourceCountryIndex]->getNumberOfArmies() == 1) {
                cout << "There is only 1 army left in attacking country" << endl;
                break;
            }
            if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() == 0) {
                cout << "There is no army left in defending country" << endl;
                player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->removeCountry(
                        player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
                player->addCountry(player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
                player->getHand()->draw(player->getMap()->getDeck());
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
                if (player->getCountries()[sourceCountryIndex]->getNumberOfArmies() >= 4) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and 3 " << endl;
                    cin >> numberOfAttackerDices;
                    if (numberOfAttackerDices < 1 || numberOfAttackerDices > 3) {
                        cout << "Invalid number! Please try again." << endl;
                    } else {
                        break;
                    }
                } else if (player->getCountries()[sourceCountryIndex]->getNumberOfArmies() < 4 &&
                           player->getCountries()[sourceCountryIndex]->getNumberOfArmies() > 1) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and "
                         << player->getCountries()[sourceCountryIndex]->getNumberOfArmies() - 1 << endl;
                    cin >> numberOfAttackerDices;
                    if (numberOfAttackerDices < 1 || numberOfAttackerDices > player->getCountries()[sourceCountryIndex]->getNumberOfArmies() - 1) {
                        cout << "Invalid number! Please try again." << endl;
                    } else {
                        break;
                    }
                }
            }
            player->getDice()->roll(numberOfAttackerDices);
            cout << "DEFENDER TURN TO CHOOSE NUMBER OF DICE" << endl;
            while (true)
            {
                winCounter = 0;
                loseCounter = 0;
                if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() >= 2) {
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
                else if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() == 1) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and " << player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() << endl;
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
            player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->roll(numberOfDefenderDices);
            cout << "Your dice value:" << endl;
            for (int i = 0; i < player->getDice()->get_value().size(); i++) {
                cout << player->getDice()->get_value()[i] << " ";
            }
            cout << endl;
            cout << "Defender dice value:" << endl;
            for (int i = 0; i < player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->get_value().size(); i++) {
                cout << *(player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->get_value()[i]) << " ";
            }
            cout << endl;
            int loop = numberOfAttackerDices< numberOfDefenderDices ? numberOfAttackerDices: numberOfDefenderDices;
            for (int i = 0; i < loop; i++) {
                if (player->getDice()->get_value()[i] > (player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getDice()->get_value()[i]))
                    winCounter++;
                else
                    loseCounter++;
            }
            player->getCountries()[sourceCountryIndex]->addArmies(-loseCounter);
            player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(-winCounter);
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

    cout << "--------------------ATTACK PHASE END--------------------------" << endl;
}

void Human::fortify(Player *player) {
    bool fortifyFlag = false;
    int sourceCountryIndex = 0;
    int targetCountryIndex = 0;
    int changeArmy = 0;
    cout << "--------------------FORTIFICATION PHASE START--------------------------" << endl;
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
        cout << "--------------------This is your information-----------------------" << endl;
        player->showInformation();
        cout << "----------------------------------------------------------------------" << endl;
        cout<<"Choose the index of SOURCE country "<<endl;
        while (true) {
            cin >> sourceCountryIndex;
            if (sourceCountryIndex<0 || sourceCountryIndex>player->getCountries().size() - 1|| player->getCountries()[sourceCountryIndex]->getNumberOfArmies() <2)
                cout << "Invalid input,please input valid index of source country which have enough armies(>=2)" << endl;
            else
                break;
        }
        cout << "This is the neighbor information of the source country" << endl;

        for (int i = 0; i < player->getCountries()[sourceCountryIndex]->getNeigbors().size(); i++) {
            cout << "Index " << i <<
                 " Country:" << player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getName()<<
                 "  Army:" << player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getNumberOfArmies() <<
                 "  Owner: "<<player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getOwner()->getName()<<endl;
        }
        cout << "Choose the index of TARGET country " << endl;
        while (true) {
            cin >> targetCountryIndex;
            if (targetCountryIndex<0 || targetCountryIndex>player->getCountries()[sourceCountryIndex]->getNeigbors().size() - 1)
                cout << "invalid input" << endl;
            else if ((player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getOwner()->getName().compare(player->getName()) != 0))
                cout<< "PLEASE CHOOSE THE COUNTRY YOU OWN !!"<<endl;
            else
                break;
        }
        cout << "Choose the numbers of armies you want to move" << endl;
        while (true) {
            cin >> changeArmy;
            if (changeArmy<=0 || changeArmy> player->getCountries()[sourceCountryIndex]->getNumberOfArmies()-1)
                cout << "Invalid input,X must be in the range [1 to(number of armies on the source country - 1)]" << endl;
            else
                break;
        }
        player->getCountries()[sourceCountryIndex]->addArmies(-changeArmy);
        player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(changeArmy);
        cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
        player->showInformation();
        cout << "----------------------------------------------------------------------" << endl;
        cout << "--------------------FORTIFICATION PHASE END--------------------------" << endl;
    }
    else {
        cout << "--------------------FORTIFICATION PHASE END--------------------------" << endl;

    }

}

