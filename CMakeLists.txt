cmake_minimum_required(VERSION 3.15)
project(Risk)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(ConquestMap)
include_directories(Maps)

add_executable(Risk
        ConquestMap/Alabama.map
        Maps/canada.map
        Maps/estonia.map
        Maps/europe.map
        Maps/sw_baltic.map
        Maps/test.map
        CardDriver.cpp
        Cards.cpp
        Cards.h
        Dice.cpp
        Dice.h
        DiceDriver.cpp
        GameEngine.cpp
        GameEngine.h
        GameEnginerDriver.cpp
        GameObservers.cpp
        GameObservers.h
        Map.cpp
        Map.h
        MapDriver.cpp
        MapLoader.cpp
        MapLoader.h
        MapLoaderDriver.cpp
        Player.cpp
        Player.h
        PlayerDriver.cpp
        PlayerStrategies.cpp
        PlayerStrategies.h)
