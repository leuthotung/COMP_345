//
// Created by yunwei yang on 2019/9/30.
//

#include <iostream>
#include <vector>
#include "Dice.h"
#include <time.h>

using namespace std;

//default generator
Dice::Dice(){
    number=new int(0);
    numbers[0]=new int(0);
    numbers[1]=new int(0);
    numbers[2]=new int(0);
    numbers[3]=new int(0);
    numbers[4]=new int(0);
    numbers[5]=new int(0);
}

//return the rolled numbers in a vector container
vector<int *> Dice::get_value() {
    return value;
}

//ask user the number of dices to be rolled and put the rolled numbers into a vector container
void Dice::roll() { //should return value of the roll and must be sorted
    int numberOfDices = 0;
    bool A = true;
    while (A) {
        cout << "How many dices would you like to roll? Please enter a number between 1 and 3: " << endl;
        cin >> numberOfDices;
        if (numberOfDices < 1 || numberOfDices > 3) {
            cout << "Invalid number! Please try again." << endl;
        } else {
            A = false;
        }
    }
    *number = *number + numberOfDices;
    for (int i = 0; i < numberOfDices; i++) {
        srand(time(NULL));// This seeds the random number generator
        value.push_back(new int(rand() % 6 + 1));//This generates a random number between 1 and 6
        (*numbers[*(value.back()) - 1])++;
    }
}

//return the rolled time for a given number of a dice object
int Dice::get_rolled_times(int i) {
    if (i < 1 || i > 6) {
        cout << "Invalid number! Please try again." << endl;
        return -1;
    }
    cout << i << " has been rolled " << *numbers[i - 1] << " times." << endl;
    return *numbers[i - 1];
}

//return the percentage of rolled time for a given number of a dice object
double Dice::get_percentage(int i) {
    if (i < 1 || i > 6) {
        cout << "Invalid number! Please try again." << endl;
        return -1.0;
    }
    int time, total_times;
    double percentage;
    time = *numbers[i - 1];
    total_times = *number;
    percentage = (double) time / (double) total_times;
    cout << "The percentage of " << i << " that has been rolled is " << percentage << "." << endl;
    return percentage;
}

//destructor
Dice::~Dice(){

}