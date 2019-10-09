//
// Created by tungleu on 10/6/19.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/*int main(){
     ifstream file("/home/tungleu/CLionProjects/COMP_345/Maps/europe.map");
     string line;
     //bool hasContinents = false;

     while(getline(file,line)&& line != "[continents]\r") {}
     cout<<"THESE ARE THE CONTINENTS"<<endl;
     while(getline(file,line) && line != "\r"){
         //cout << line << endl;
         string continent = line.substr(0,line.find(" "));
         int value = stoi(line.substr(line.find(" ")+1));
         cout<<continent<<" and " << value <<endl;
     }
     while(getline(file,line)&& line != "[countries]\r") {}
     cout<<"THESE ARE THE COUNTRIES"<<endl;
     while(getline(file,line) && line != "\r"){
         stringstream ss(line);
         string word;
         char delim = ' ';
         vector<string> lineSplit;
         while(getline(ss,word,delim)){
             lineSplit.push_back(word);
         }
         cout << lineSplit[1] << endl;
     }
     while(getline(file,line)&& line != "[borders]\r") {}
     cout<<"THESE ARE THE BORDERS"<<endl;
     while(getline(file,line) && line != "\r"){
         stringstream ss(line);
         string word;
         char delim = ' ';
         vector<string> lineSplit;
         while(getline(ss,word,delim)){
             lineSplit.push_back(word);
         }
         
         cout << stoi(lineSplit[0]) << endl;
     }*//*





    //cout << line << endl;
     //cout<<hasContinents;





     }
*/

