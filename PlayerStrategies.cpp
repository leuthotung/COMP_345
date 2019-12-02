/*//*/
// Created by tungleu on 11/17/19.
//

#include "PlayerStrategies.h"
#include "Player.h"

static void clear() {
    for (int i = 0; i < 50; i++) {
        cout << "\n";
    }
}

void Human::reinforce(Player *player) {
    cout << "------------------REINFORCE PHASE START-------------------------" << endl;
    int armyCounter = 0;
    bool exchangeFlag = false;
    int armiesFromNumberOfCountries = player->getCountries().size() / 3;
    cout << player->getName() << " has " << armiesFromNumberOfCountries << " armies for occupying "
         << player->getCountries().size() << " countries" << endl;
    armyCounter += armiesFromNumberOfCountries;
    armyCounter += player->armiesFromContinent();
    cout << "Do you want to exchange card??(input 0(false) or 1(true))" << endl;
    while (true) {
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

    cout << player->getName() << " will have " << armyCounter << " armies in this reinforcement stage" << endl;

    while (armyCounter > 0) {
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
                    if (numberOfArmiesToAdd > armyCounter || numberOfArmiesToAdd < 0) {
                        cout << "Please add valid number of armies!! Choose again" << endl;
                    } else {
                        cout << "Added " << numberOfArmiesToAdd << " army to country "
                             << player->getCountries()[countryIndex]->getName()
                             << endl;
                        player->getCountries()[countryIndex]->addArmies(numberOfArmiesToAdd);
                        indexValid = true;
                        armyCounter = armyCounter - numberOfArmiesToAdd;
                        validNumber = true;
                        player->setObserverSelect(0);
                        player->Notify();

                    }
                }
            }
        }
    }
    cout << "ALL ARMIES ARE PLACED SUCCESSFULLY" << endl;
    bool nextPhaseFlag = false;
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
        if (nextPhaseFlag) {
            clear();
            break;
        } else
            cout << "ALL ARMIES ARE PLACED SUCCESSFULLY, NOTHING TO DO IN REINFORCE PHASE" << endl;
    }
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------REINFORCE PHASE ENDS-------------------------" << endl;
}

void Human::attack(Player *player) {
    cout << "------------------ATTACK PHASE START-------------------------" << endl;
    bool attackFlag = false;
    bool continueFlag = false;
    int sourceCountryIndex = 0;
    int targetCountryIndex = 0;
    int winCounter = 0;
    int loseCounter = 0;
    cout << "Do you want to attack? (input 0(false) or 1(true) )" << endl;
    while (true) {
        if (cin >> attackFlag)
            break;
        else {
            cout << "invalid input" << endl;
            cin.clear();
            cin.ignore();
        }
    }

    while (attackFlag) {
        cout << "Choose the index of SOURCE country " << endl;
        while (true) {
            cin >> sourceCountryIndex;
            if (sourceCountryIndex < 0 || sourceCountryIndex > player->getCountries().size() - 1 ||
                player->getCountries()[sourceCountryIndex]->getNumberOfArmies() < 2)
                cout << "Invalid input,please input valid index of source country who have enough armies(>=2)" << endl;
            else
                break;
        }
        cout << "--------------This is neighbors information of the source country-----------------" << endl;
        for (int i = 0; i < player->getCountries()[sourceCountryIndex]->getNeigbors().size(); i++) {
            cout << "Index" << i << " Country:"
                 << player->getCountries()[sourceCountryIndex][sourceCountryIndex].getNeigbors().at(i)->getName()
                 << "  Army:" << player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getNumberOfArmies() <<
                 "  Owner: " << player->getCountries()[sourceCountryIndex][sourceCountryIndex].getNeigbors().at(
                    i)->getOwner()->getName() << endl;
        }
        cout << "Choose the index of TARGET country " << endl;
        while (true) {
            cin >> targetCountryIndex;
            if (targetCountryIndex < 0 ||
                targetCountryIndex > player->getCountries()[sourceCountryIndex]->getNeigbors().size() - 1) {
                cout << "Invalid input" << endl;
            } else if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                    targetCountryIndex)->getOwner()->getName().compare(player->getName()) == 0) {
                cout << "Invalid input, please choose enemy country" << endl;
            } else
                break;
        }
        while (true) {
            cout << "There are " << player->getCountries()[sourceCountryIndex]->getNumberOfArmies()
                 << " in attacking country"
                 << endl;
            cout << "There are "
                 << player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                         targetCountryIndex)->getNumberOfArmies()
                 << " in defending country" << endl;
            if (player->getCountries()[sourceCountryIndex]->getNumberOfArmies() == 1) {
                cout << "There is only 1 army left in attacking country" << endl;
                break;
            }
            if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->getNumberOfArmies() ==
                0) {
                cout << "There is no army left in defending country" << endl;
                player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                        targetCountryIndex)->getOwner()->removeCountry(
                        player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
                player->addCountry(player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex));
                player->getHand()->draw(player->getMap()->getDeck());
                player->setObserverSelect(1);
                player->Notify();
                int changeArmy = 0;
                cout
                        << "Please move a number of armies from the attacking country to the attacked country,in the range [1 to "
                        << player->getCountries()[sourceCountryIndex]->getNumberOfArmies() - 1 << "]" << endl;
                while (true) {
                    cin >> changeArmy;
                    if (changeArmy <= 0 ||
                        changeArmy > player->getCountries()[sourceCountryIndex]->getNumberOfArmies() - 1)
                        cout << "invalid input,X must be in the range [1 to "
                             << player->getCountries()[sourceCountryIndex]->getNumberOfArmies() - 1 << "]" << endl;
                    else
                        break;
                }
                player->getCountries()[sourceCountryIndex]->addArmies(-changeArmy);
                player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(changeArmy);
                break;
            }
            cout << "Do you want to continue attack current country?(input 0(false) or 1(true))" << endl;
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
                    if (numberOfAttackerDices < 1 ||
                        numberOfAttackerDices > player->getCountries()[sourceCountryIndex]->getNumberOfArmies() - 1) {
                        cout << "Invalid number! Please try again." << endl;
                    } else {
                        break;
                    }
                }
            }
            player->getDice()->roll(numberOfAttackerDices);
            cout << "DEFENDER TURN TO CHOOSE NUMBER OF DICE" << endl;
            if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                    targetCountryIndex)->getOwner()->getStrategy()->getName() == "Human") {
                while (true) {
                    winCounter = 0;
                    loseCounter = 0;
                    if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                            targetCountryIndex)->getNumberOfArmies() >= 2) {
                        cout << "How many dices would you like to roll? Please enter a number between 1 and 2 " << endl;
                        cin >> numberOfDefenderDices;
                        if (numberOfDefenderDices < 1 || numberOfDefenderDices > 2) {
                            cout << "Invalid number! Please try again." << endl;
                        } else {
                            break;
                        }
                    } else if (player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                            targetCountryIndex)->getNumberOfArmies() == 1) {
                        cout << "How many dices would you like to roll? Please enter a number between 1 and "
                             << player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                                     targetCountryIndex)->getNumberOfArmies() << endl;
                        cin >> numberOfDefenderDices;
                        if (numberOfDefenderDices != 1) {
                            cout << "Invalid number! Please try again." << endl;
                        } else {
                            break;
                        }
                    } else
                        break;
                }
            }
            else{
                numberOfDefenderDices=rand()%2+1;
            }
            player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                    targetCountryIndex)->getOwner()->getDice()->roll(numberOfDefenderDices);
            cout << "Your dice value:" << endl;
            for (int i = 0; i < player->getDice()->get_value().size(); i++) {
                cout << *player->getDice()->get_value()[i] << " ";
            }
            cout << endl;
            cout << "Defender dice value:" << endl;
            for (int i = 0; i < player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                    targetCountryIndex)->getOwner()->getDice()->get_value().size(); i++) {
                cout << *(player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                        targetCountryIndex)->getOwner()->getDice()->get_value()[i]) << " ";
            }
            cout << endl;
            int loop = numberOfAttackerDices < numberOfDefenderDices ? numberOfAttackerDices : numberOfDefenderDices;
            for (int i = 0; i < loop; i++) {
                if (player->getDice()->get_value()[i] > (player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                        targetCountryIndex)->getOwner()->getDice()->get_value()[i]))
                    winCounter++;
                else
                    loseCounter++;
            }
            player->getCountries()[sourceCountryIndex]->addArmies(-loseCounter);
            player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(-winCounter);
        }
        cout << "Do you want to attack again ?(input 0(false) or 1(true))" << endl;
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
    clear();
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------ATTACK PHASE ENDS-------------------------" << endl;

}

void Human::fortify(Player *player) {
    cout << "------------------FORTIFICATION PHASE START-------------------------" << endl;
    bool fortifyFlag = false;
    int sourceCountryIndex = 0;
    int targetCountryIndex = 0;
    int changeArmy = 0;
    cout << "Do you want to fortify? (input 0(false) or 1(true) )" << endl;
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
        cout << "Choose the index of SOURCE country " << endl;
        while (true) {
            cin >> sourceCountryIndex;
            if (sourceCountryIndex < 0 || sourceCountryIndex > player->getCountries().size() - 1 ||
                player->getCountries()[sourceCountryIndex]->getNumberOfArmies() < 2)
                cout << "Invalid input,please input valid index of source country which have enough armies(>=2)"
                     << endl;
            else
                break;
        }
        cout << "This is the neighbor information of the source country" << endl;

        for (int i = 0; i < player->getCountries()[sourceCountryIndex]->getNeigbors().size(); i++) {
            cout << "Index " << i <<
                 " Country:" << player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getName() <<
                 "  Army:" << player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getNumberOfArmies() <<
                 "  Owner: " << player->getCountries()[sourceCountryIndex]->getNeigbors().at(i)->getOwner()->getName()
                 << endl;
        }
        cout << "Choose the index of TARGET country " << endl;
        while (true) {
            cin >> targetCountryIndex;
            if (targetCountryIndex < 0 ||
                targetCountryIndex > player->getCountries()[sourceCountryIndex]->getNeigbors().size() - 1)
                cout << "invalid input" << endl;
            else if ((player->getCountries()[sourceCountryIndex]->getNeigbors().at(
                    targetCountryIndex)->getOwner()->getName().compare(player->getName()) != 0))
                cout << "PLEASE CHOOSE THE COUNTRY YOU OWN !!" << endl;
            else
                break;
        }
        cout << "Choose the numbers of armies you want to move" << endl;
        while (true) {
            cin >> changeArmy;
            if (changeArmy <= 0 || changeArmy > player->getCountries()[sourceCountryIndex]->getNumberOfArmies() - 1)
                cout << "Invalid input,X must be in the range [1 to(number of armies on the source country - 1)]"
                     << endl;
            else
                break;
        }
        player->getCountries()[sourceCountryIndex]->addArmies(-changeArmy);
        player->getCountries()[sourceCountryIndex]->getNeigbors().at(targetCountryIndex)->addArmies(changeArmy);
        player->setObserverSelect(0);
        player->Notify();
        bool nextPhaseFlag = false;
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
            if (nextPhaseFlag) {
                clear();
                break;
            } else
                cout << "PLEASE END YOUR PHASE AFTER CHECKING YOUR INFORMATION" << endl;
        }
    } else {
        clear();

    }
    cout << "------------------FORTIFICATION PHASE ENDS-------------------------" << endl;
}

void Aggressive::reinforce(Player *player) {
    cout << "------------------REINFORCE PHASE START-------------------------" << endl;
    int armyCounter = 0;
    int armiesFromNumberOfCountries = player->getCountries().size() / 3;
    cout << player->getName() << " has " << armiesFromNumberOfCountries << " armies for occupying "
         << player->getCountries().size() << " countries" << endl;
    armyCounter += armiesFromNumberOfCountries;
    armyCounter += player->armiesFromContinent();
    armyCounter += player->getHand()->exchange();


    cout << player->getName() << " will have " << armyCounter << " armies  in this reinforcement stage" << endl;
    int maxArmies = 0;
    Country *strongestCountry;
    for (int i = 0; i < player->getCountries().size(); i++) {
        if (player->getCountries()[i]->getNumberOfArmies() > maxArmies) {
            strongestCountry = player->getCountries()[i];
        }
    }
    strongestCountry->addArmies(armyCounter);
    cout << "Added " << armyCounter << " army to country "
         << strongestCountry->getName()
         << endl;
    player->setObserverSelect(0);
    player->Notify();

    cout << "ALL ARMIES ARE PLACED SUCCESSFULLY" << endl;

    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------REINFORCE PHASE ENDS-------------------------" << endl;

}

void Aggressive::attack(Player *player) {
    player->setObserverSelect(0);
    player->Notify();

    cout << "------------------ATTACK PHASE START-------------------------" << endl;
    int maxArmies = 0;
    Country *strongestCountry;
    for (int i = 0; i < player->getCountries().size(); i++) {
        if (player->getCountries()[i]->getNumberOfArmies() > maxArmies) {
            strongestCountry = player->getCountries()[i];
        }
    }
    vector<Country *> countriesToAttack;
    for (int i = 0; i < strongestCountry->getNeigbors().size(); i++) {
        if (strongestCountry->getNeigbors()[i]->getOwner()->getName() != player->getName()) {
            countriesToAttack.push_back(strongestCountry->getNeigbors()[i]);
        }
    }
    for (int i = 0; i < countriesToAttack.size(); i++) {

        while (true) {

            Country *defender = countriesToAttack[i];
            cout << strongestCountry->getName() << " is attacking " << defender->getName()
                 << " DEFENDER COUNTRY OWNER: " << defender->getOwner()->getName() << endl;
            if (defender->getNumberOfArmies() == 0) {
                cout << "There is no army left in defending country " << endl;
                defender->getOwner()->removeCountry(defender);
                player->addCountry(defender);
                player->getHand()->draw(player->getMap()->getDeck());
                player->setObserverSelect(1);
                player->Notify();

                break;
            }
            int numberOfAttackerDices = 0, numberOfDefenderDices = 0;
            if (strongestCountry->getNumberOfArmies() >= 4) {
                numberOfAttackerDices = 3;
            } else if (strongestCountry->getNumberOfArmies() < 4 && strongestCountry->getNumberOfArmies() > 1) {
                numberOfAttackerDices = 2;
            } else {
                cout << "This country cannot attack anymore since there is only 1 army left in the country" << endl;
                break;
            }

            cout << "DEFENDER TURN TO CHOOSE NUMBER OF DICE" << endl;
            if (defender->getOwner()->getStrategy()->getName() == "Human") {
                while (true) {
                    if (defender->getNumberOfArmies() >= 2) {
                        cout << "How many dices would you like to roll? Please enter a number between 1 and 2 " << endl;
                        cin >> numberOfDefenderDices;
                        if (numberOfDefenderDices < 1 || numberOfDefenderDices > 2) {
                            cout << "Invalid number! Please try again." << endl;
                        } else {
                            break;
                        }
                    } else if (defender->getNumberOfArmies() == 1) {
                        numberOfDefenderDices = 1;
                    } else
                        break;

                }
            }
            else{
                numberOfDefenderDices=rand()%2+1;
            }
            player->getDice()->roll(numberOfAttackerDices);
            defender->getOwner()->getDice()->roll(numberOfDefenderDices);
            cout << "Your dice value:" << endl;
            for (int i = 0; i < player->getDice()->get_value().size(); i++) {
                cout << *player->getDice()->get_value()[i] << " ";
            }
            cout << endl;
            cout << "Defender dice value:" << endl;
            for (int i = 0; i < defender->getOwner()->getDice()->get_value().size(); i++) {
                cout << *defender->getOwner()->getDice()->get_value()[i] << " ";
            }
            cout << endl;
            //Decide win or lose
            int winCounter = 0;
            int loseCounter = 0;
            int loop = numberOfAttackerDices < numberOfDefenderDices ? numberOfAttackerDices : numberOfDefenderDices;
            for (int i = 0; i < loop; i++) {
                if (player->getDice()->get_value()[i] > defender->getOwner()->getDice()->get_value()[i])
                    winCounter++;
                else
                    loseCounter++;
            }

            strongestCountry->addArmies(-loseCounter);
            defender->addArmies(-winCounter);
        }


    }
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------ATTACK PHASE ENDS-------------------------" << endl;

}

void Aggressive::fortify(Player *player) {
    cout << "------------------FORTIFICATION PHASE START-------------------------" << endl;
    int maxArmies = 0;
    Country *strongestCountry;
    for (int i = 0; i < player->getCountries().size(); i++) {
        if (player->getCountries()[i]->getNumberOfArmies() > maxArmies) {
            strongestCountry = player->getCountries()[i];
        }
    }
    vector<Country *> ownedNeighbors;
    for (int i = 0; i < strongestCountry->getNeigbors().size(); i++) {
        if (strongestCountry->getNeigbors()[i]->getOwner()->getName() == player->getName()) {
            ownedNeighbors.push_back(strongestCountry->getNeigbors()[i]);
        }
    }
    for (int i = 0; i < ownedNeighbors.size(); i++) {
        if (ownedNeighbors[i]->getNumberOfArmies() > 1) {
            int changeArmy = ownedNeighbors[i]->getNumberOfArmies() - 1;
            strongestCountry->addArmies(changeArmy);
            ownedNeighbors[i]->addArmies(-changeArmy);
            player->setObserverSelect(0);
            player->Notify();


            break;
        }
    }
    player->setObserverSelect(0);
    player->Notify();
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------FORTIFICATION PHASE ENDS-------------------------" << endl;
}


void Benevolent::reinforce(Player *player) {

    cout << "------------------REINFORCE PHASE START-------------------------" << endl;
    Country *weakestCountry = player->getCountries()[0];
    for (int i = 0; i < player->getCountries().size(); i++) {
        if (player->getCountries()[i]->getNumberOfArmies() < weakestCountry->getNumberOfArmies()) {
            weakestCountry = player->getCountries()[i];
        }
    }
    int armyCounter = 0;
    int armiesFromNumberOfCountries = player->getCountries().size() / 3;
    cout << player->getName() << " has " << armiesFromNumberOfCountries << " armies for occupying "
         << player->getCountries().size() << " countries" << endl;
    armyCounter += armiesFromNumberOfCountries;
    armyCounter += player->armiesFromContinent();
    armyCounter += player->getHand()->exchange();


    cout << player->getName() << " will have " << armyCounter << " armies in this reinforcement stage" << endl;
    weakestCountry->addArmies(armyCounter);
    cout << "Added " << armyCounter << " army to country "
         << weakestCountry->getName()
         << endl;
    cout << "ALL ARMIES ARE PLACED SUCCESSFULLY" << endl;
    player->setObserverSelect(0);
    player->Notify();
    bool nextPhaseFlag = false;
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------REINFORCE PHASE ENDS-------------------------" << endl;

}

void Benevolent::attack(Player *player) {
    cout << "------------------ATTACK PHASE START-------------------------" << endl;
    cout << "---Player is Benevolent, no attack will be occurred----------------" << endl;
}

void Benevolent::fortify(Player *player) {
    cout << "------------------FORTIFICATION PHASE START-------------------------" << endl;
    int maxArmies = 0;
    Country *weakestCountry = player->getCountries()[0];
    for (int i = 0; i < player->getCountries().size(); i++) {
        if (player->getCountries()[i]->getNumberOfArmies() < weakestCountry->getNumberOfArmies()) {
            weakestCountry = player->getCountries()[i];
        }
    }
    vector<Country *> ownedNeighbors;
    for (int i = 0; i < weakestCountry->getNeigbors().size(); i++) {
        if (weakestCountry->getNeigbors()[i]->getOwner()->getName() == player->getName()) {
            ownedNeighbors.push_back(weakestCountry->getNeigbors()[i]);
        }
    }
    for (int i = 0; i < ownedNeighbors.size(); i++) {
        if (ownedNeighbors[i]->getNumberOfArmies() > 1) {
            int changeArmy = ownedNeighbors[i]->getNumberOfArmies() - 1;
            weakestCountry->addArmies(changeArmy);
            ownedNeighbors[i]->addArmies(-changeArmy);
            break;

        }
    }
    player->setObserverSelect(0);
    player->Notify();

    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------FORTIFICATION PHASE ENDS-------------------------" << endl;

}

void Random::reinforce(Player *player) {
    cout << "------------------REINFORCE PHASE START-------------------------" << endl;
    int armyCounter = 0;
    int armiesFromNumberOfCountries = player->getCountries().size() / 3;
    cout << player->getName() << " has " << armiesFromNumberOfCountries << " armies for occupying "
         << player->getCountries().size() << " countries" << endl;
    armyCounter += armiesFromNumberOfCountries;
    armyCounter += player->armiesFromContinent();
    armyCounter += player->getHand()->exchange();
    cout << player->getName() << " will have " << armyCounter << " armies  in this reinforcement stage" << endl;
    //decide which country to reinforce
    int randomNumber = rand() % player->getCountries().size();
    Country *countryToReinforce = player->getCountries()[randomNumber];
    countryToReinforce->addArmies(armyCounter);
    cout << "Added " << armyCounter << " army to country "
         << countryToReinforce->getName()
         << endl;
    player->setObserverSelect(0);
    player->Notify();

    cout << "ALL ARMIES ARE PLACED SUCCESSFULLY" << endl;
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "--------------------REINFORCE PHASE END--------------------------" << endl;
}

void Random::attack(Player *player) {
    player->setObserverSelect(0);
    player->Notify();

    cout << "------------------ATTACK PHASE START-------------------------" << endl;
    //decide which country to attack
    vector<Country*> countries;
    for(Country* c:player->getCountries()){
        if(c->getNumberOfArmies()>1){
            countries.push_back(c);
        }
    }
    int randomNumber = rand() % countries.size();
    Country *countryToAttack = countries[randomNumber];
    //decide which country to be attacked
    int anotherRandomNumber = rand() % countryToAttack->getNeigbors().size();
    Country *countryToBeAttacked = countryToAttack->getNeigbors()[anotherRandomNumber];
    //decide whether to attack or not
    bool attackFlag;
    if (rand() % countryToAttack->getNumberOfArmies() == 0) {
        attackFlag = false;
    } else {
        attackFlag = true;
    }
    while (attackFlag) {
        cout << countryToAttack->getName() << " is attacking " << countryToBeAttacked->getName()
             << " DEFENDER COUNTRY OWNER: " << countryToBeAttacked->getOwner()->getName() << endl;
        if (countryToBeAttacked->getNumberOfArmies() == 0) {
            cout << "There is no army left in defending country " << endl;
            countryToBeAttacked->getOwner()->removeCountry(countryToBeAttacked);
            player->addCountry(countryToBeAttacked);
            player->getHand()->draw(player->getMap()->getDeck());
            player->setObserverSelect(1);
            player->Notify();

            break;
        }
        int numberOfAttackerDices = 0, numberOfDefenderDices = 0;
        if (countryToAttack->getNumberOfArmies() >= 4) {
            numberOfAttackerDices = rand() % 3 + 1;
        } else if (countryToAttack->getNumberOfArmies() < 4 && countryToAttack->getNumberOfArmies() > 1) {
            numberOfAttackerDices = rand() % 2 + 1;
        } else {
            cout << "This country cannot attack anymore since there is only 1 army left in the country" << endl;
            break;
        }

        cout << "DEFENDER TURN TO CHOOSE NUMBER OF DICE" << endl;
        if (countryToBeAttacked->getOwner()->getStrategy()->getName() == "Human") {
            while (true) {
                if (countryToBeAttacked->getNumberOfArmies() >= 2) {
                    cout << "How many dices would you like to roll? Please enter a number between 1 and 2 " << endl;
                    cin >> numberOfDefenderDices;
                    if (numberOfDefenderDices < 1 || numberOfDefenderDices > 2) {
                        cout << "Invalid number! Please try again." << endl;
                    } else {
                        break;
                    }
                } else if (countryToBeAttacked->getNumberOfArmies() == 1) {
                    numberOfDefenderDices = 1;
                } else
                    break;

            }
        }
        else{
            numberOfDefenderDices=rand()%2+1;
        }
        player->getDice()->roll(numberOfAttackerDices);
        countryToBeAttacked->getOwner()->getDice()->roll(numberOfDefenderDices);
        cout << "Your dice value:" << endl;
        for (int i = 0; i < player->getDice()->get_value().size(); i++) {
            cout << *player->getDice()->get_value()[i] << " ";
        }
        cout << endl;
        cout << "Defender dice value:" << endl;
        for (int i = 0; i < countryToBeAttacked->getOwner()->getDice()->get_value().size(); i++) {
            cout << *countryToBeAttacked->getOwner()->getDice()->get_value()[i] << " ";
        }
        cout << endl;
        //Decide win or lose
        int winCounter = 0;
        int loseCounter = 0;
        int loop = numberOfAttackerDices < numberOfDefenderDices ? numberOfAttackerDices : numberOfDefenderDices;
        for (int i = 0; i < loop; i++) {
            if (player->getDice()->get_value()[i] > countryToBeAttacked->getOwner()->getDice()->get_value()[i])
                winCounter++;
            else
                loseCounter++;
        }

        countryToAttack->addArmies(-loseCounter);
        countryToBeAttacked->addArmies(-winCounter);

        if (countryToAttack->getNumberOfArmies() == 0) {
            attackFlag = false;
        }
    }
    cout << "NOTHING TO DO IN ATTACK PHASE" << endl;
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------ATTACK PHASE ENDS-------------------------" << endl;
}

void Random::fortify(Player *player) {
    cout << "------------------FORTIFICATION PHASE START-------------------------" << endl;
    //decide which country to fortify
    int randomNumber = rand() % player->getCountries().size();
    Country *countryToFortify = player->getCountries()[randomNumber];
    //decide where to move army from
    vector<Country *> domesticNeighbours;
    for (Country *c:countryToFortify->getNeigbors()) {
        if (c->getOwner() == player&&c->getNumberOfArmies()>0) {
            domesticNeighbours.push_back(c);
        }
    }
    if (domesticNeighbours.size() != 0) {
        int anotherRandomNumber = rand() % domesticNeighbours.size();
        Country *countryToMoveArmy = domesticNeighbours[anotherRandomNumber];
        //decide how many army to be moved
        int randomCount = rand() % countryToMoveArmy->getNumberOfArmies();
        countryToMoveArmy->setNumberOfArmies(countryToMoveArmy->getNumberOfArmies() - randomCount);
        countryToFortify->setNumberOfArmies(countryToFortify->getNumberOfArmies() + randomCount);

        player->setObserverSelect(0);
        player->Notify();
        cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
        player->showInformation();
    }
    else{
        cout<<"Theres no domestic neighbor in randomed country "<<endl;
    }
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------FORTIFICATION PHASE ENDS-------------------------" << endl;
}

void Cheater::reinforce(Player *player) {
    cout << "------------------REINFORCE PHASE START-------------------------" << endl;
    for (Country *c:player->getCountries()) {
        c->setNumberOfArmies(c->getNumberOfArmies() * 2);
    }
    player->setObserverSelect(0);
    player->Notify();
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "--------------------REINFORCE PHASE END--------------------------" << endl;
}

void Cheater::attack(Player *player) {
    player->setObserverSelect(0);
    player->Notify();

    cout << "------------------ATTACK PHASE START-------------------------" << endl;
    for (Country *c:player->getCountries()) {
        for (Country *neighbour:c->getNeigbors()) {
            if (neighbour->getOwner() != player) {
                neighbour->getOwner()->removeCountry(neighbour);
                player->addCountry(neighbour);
            }
        }
    }
    cout << "NOTHING TO DO IN ATTACK PHASE" << endl;
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------ATTACK PHASE ENDS-------------------------" << endl;
}

void Cheater::fortify(Player *player) {
    cout << "------------------FORTIFICATION PHASE START-------------------------" << endl;
    for (Country *c:player->getCountries()) {
        if (c->hasForeignNeighbors()) {
            c->setNumberOfArmies(c->getNumberOfArmies() * 2);
        }
    }
    player->setObserverSelect(0);
    player->Notify();
    cout << "--------------------THIS IS YOUR INFORMATION-----------------------" << endl;
    player->showInformation();
    cout << "----------------------------------------------------------------------" << endl;
    cout << "------------------FORTIFICATION PHASE ENDS-------------------------" << endl;
}