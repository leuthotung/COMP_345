//
// Created by yunwei yang on 2019/9/30.
//

#include <iostream>
#include "Dice.h"

using namespace std;

int main() {
    Dice* d=new Dice();
    d->roll();
    d->roll();
    d->roll();
    d->roll();
    d->roll();
    d->roll();
    d->roll();
    d->roll();
    d->roll();
    for (int i = 0; i < d->getValue().size(); i++) {
        cout << d->getValue()[i];
    }
    cout << endl;
    for (int i = 1; i <= 6; i++) {
        d->getRolledTimes(i);
    }
    for (int i = 1; i <= 6; i++) {
        d->getPercentage(i);
    }
};