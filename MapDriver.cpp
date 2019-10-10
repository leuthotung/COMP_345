//
// Created by tungleu on 9/29/19.
//
#include "Map.h"
#include <iostream>
#include <vector>
#include "MapLoader.h"
using namespace std;

int main() {
    Map a = readMapFile("/home/tungleu/CLionProjects/COMP_345/Maps/europe.map");




    a.print();
}

