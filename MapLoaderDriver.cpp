//
// Created by tungleu on 10/6/19.
//

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
     ifstream f("/home/tungleu/CLionProjects/COMP345/Maps/europe.map");
     string line;
     string continents;
     bool hasContinents = false;
     int count =0;
     stringstream ss;
     while(getline(f,line)){
         
         if (line == "[continents]"){
             hasContinents = true;
         }

         /*if (line == "[continents]\n"){
             hasContinents= true;
         }*/
     }


     cout<<hasContinents;


     }

