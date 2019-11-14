//
// Created by tungleu on 9/27/19.
//

#ifndef COMP345_MAPLOADER_H
#define COMP345_MAPLOADER_H
#include "Map.h"
#include <iostream>
class MapLoader{
public:
    Map readMapFile(string file);
    bool validateMapFile(string file);
};
class Adaptee{
public:
    Map readMapFile(string file);
};
class Adapter :public MapLoader {
private:
    Adaptee adaptee;
public:
    Adapter(Adaptee conquestAdaptee){
        adaptee= conquestAdaptee;
    }
    Map readMapFile(string file){
        return adaptee.readMapFile(file);

    };
};
Map readMapFile(string file);
Map readConquestMapFile(string file);
bool validateMapFile(string file);
#endif //COMP345_MAPLOADER_H
