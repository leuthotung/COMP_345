//
// Created by yunwei yang on 2019/9/30.
//

#ifndef ASSIGNMENT1_DICE_H
#define ASSIGNMENT1_DICE_H

#include <string>
#include <vector>

using namespace std;

class Dice {
private:
    vector<int *> value;
    int *number;
    int *numbers[6];
public:
    Dice();

    vector<int *> get_value();

    void roll();

    int get_rolled_times(int i);

    double get_percentage(int i);

    ~Dice();
};

#endif //ASSIGNMENT1_DICE_H
