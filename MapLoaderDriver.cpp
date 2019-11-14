//
// Created by tungleu on 10/6/19.
//
#include "Map.h"
#include "MapLoader.h"

using namespace std;

int main() {
/*    Map a = readMapFile("../Maps/europe.map");
    a.print()*/;
    //read a fail map
    /*Map b = readMapFile("../Maps/test.map");
    return 0;*/

 /*   Map a = readConquestMapFile("../ConquestMap/Alabama.map");
    a.print();*/
 //MapLoader mapload;
// Map a = mapload.readMapFile("../Maps/europe.map");
 //a.print();
 Adaptee conquest;
 Adapter readConquest(conquest);
 Map b = readConquest.readMapFile("../ConquestMap/Alabama.map");
 b.print();
    return 0;
}
