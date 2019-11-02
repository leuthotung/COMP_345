//
// Created by tungleu on 10/6/19.
//
#include "Map.h"
#include "MapLoader.h"

using namespace std;


int main() {
    Map a = readMapFile("C:\\Users\\Administrator\\source\\repos\\comp345assignment\\Maps\\europe.map");
    a.print();
    //read a fail map
    Map b = readMapFile("C:\\Users\\Administrator\\source\\repos\\comp345assignment\\Maps\\test.map");
}
