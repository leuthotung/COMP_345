//
// Created by yunwei yang on 2019/9/30.
//

#include <iostream>
#include "Dice.h"

using namespace std;

//default generator
Dice::Dice() {
    number = 0;
    numbers[0]=0;
    numbers[1]=0;
    numbers[2]=0;
    numbers[3]=0;
    numbers[4]=0;
    numbers[5]=0;
}

//return the rolled numbers in a vector container
vector<int> Dice::getValue() {
    return *value;
}

//ask user the number of dices to be rolled and put the rolled numbers into a vector container
//return the max number rolled
int Dice::roll() {
    int numberOfDices;
    bool A;
    A=true;
    while (A) {
        cout << "How many dices would you like to roll? Please enter a number between 1 and 3: " << endl;
        cin >> numberOfDices;
        if (numberOfDices < 1 || numberOfDices > 3) {
            cout << "Invalid number! Please try again.";
        } else {
            A = false;
        }
    }
    *number = *number+numberOfDices;
    // This seeds the random number generator:
    srand(time(NULL));
    int randomNumber, maxNumber = 0;
    for (int i = 0; i < numberOfDices; i++) {
        //This generates a random number between 1 and 6
        randomNumber = rand() % 6 + 1;
        if (maxNumber < randomNumber) {
            maxNumber = randomNumber;
        }
        value->push_back(randomNumber);
        switch (randomNumber) {
            case 1:
                numbers[0]++;
                break;
            case 2:
                numbers[1]++;
                break;
            case 3:
                numbers[2]++;
                break;
            case 4:
                numbers[3]++;
                break;
            case 5:
                numbers[4]++;
                break;
            case 6:
                numbers[5]++;
                break;
            default:
                break;
        }
    }
    return maxNumber;
}

//return the rolled time for a given number of a dice object
int Dice::getRolledTimes(int i) {
    switch (i) {
        case 1:
            cout << i << " has been rolled " << numbers[0] << " times." << endl;
            return numbers[0];
        case 2:
            cout << i << " has been rolled " << numbers[1] << " times." << endl;
            return numbers[1];
        case 3:
            cout << i << " has been rolled " << numbers[2] << " times." << endl;
            return numbers[2];
        case 4:
            cout << i << " has been rolled " << numbers[3] << " times." << endl;
            return numbers[3];
        case 5:
            cout << i << " has been rolled " << numbers[4] << " times." << endl;
            return numbers[4];
        case 6:
            cout << i << " has been rolled " << numbers[5] << " times." << endl;
            return numbers[5];
        default:
            cout << "Invalid number! Please try again." << endl;
            return -1;
    }
}

//return the percentage of rolled time for a given number of a dice object
double Dice::getPercentage(int i) {
    switch (i) {
        case 1:
            cout<< "The percentage of "<<i<<" that has been rolled is "<<(double)numbers[0] / (double)number<<"."<<endl;
            return (double)numbers[0] / (double)number;
        case 2:
            cout<< "The percentage of "<<i<<" that has been rolled is "<<(double)numbers[1] / (double)number<<"."<<endl;
            return (double)numbers[1] / (double)number;
        case 3:
            cout<< "The percentage of "<<i<<" that has been rolled is "<<(double)numbers[2] / (double)number<<"."<<endl;
            return (double)numbers[2] / (double)number;
        case 4:
            cout<< "The percentage of "<<i<<" that has been rolled is "<<(double)numbers[3] / (double)number<<"."<<endl;
            return (double)numbers[3] / (double)number;
        case 5:
            cout<< "The percentage of "<<i<<" that has been rolled is "<<(double)numbers[4] / (double)number<<"."<<endl;
            return (double)numbers[4] / (double)number;
        case 6:
            cout<< "The percentage of "<<i<<" that has been rolled is "<<(double)numbers[5] / (double)number<<"."<<endl;
            return (double)numbers[5] / (double)number;
        default:
            cout << "Invalid number! Please try again." << endl;
            return -1.0;
    }
}

//destructor
Dice::~Dice() {

}