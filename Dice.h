//
// Created by yunwei yang on 2019/9/30.
//

#ifndef ASSIGNMENT1_DICE_H
#define ASSIGNMENT1_DICE_H

#include <string>
#include <vector>

using namespace std;

class Dice {
    vector<int>* value;
    int* number;
    int* numbers[6];
public:
    Dice();

    vector<int> getValue();

    int roll();

    int getRolledTimes(int i);

    double getPercentage(int i);

    ~Dice();
};

#endif //ASSIGNMENT1_DICE_H
