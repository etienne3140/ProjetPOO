#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "CPU.hpp"
#include "MEMORY.hpp"

using namespace std;

#ifndef DISPLAY_H
#define DISPLAY_H



class DISPLAY {
    private:
        int RefAct;
        string SOURCE;
    public:
        int REFRESH;
        int Iter;
        void load(const string& fileName);      
        void simulate(MEMORY* memory);
        void PrintDISPLAY();
        DISPLAY() :
            Iter(0),
            REFRESH(0),
            SOURCE(""),
            RefAct(0)
            {};
};



void DISPLAY::load(const string& fileName) {
        std::ifstream file("data/"+fileName);

        if (!file) {
            std::cerr << "Impossible d'ouvrir le file " << fileName << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(':');
            std::string cle = line.substr(0, pos);
            std::string value = line.substr(pos + 2); 
            if (cle == "REFRESH") {
                REFRESH = std::stoi(value); 
            } 
            else if (cle == "SOURCE"){
                SOURCE = value;
            }
        }
        file.close();
}

void DISPLAY::simulate(MEMORY* memory){
    RefAct++;
    DataValue result;
    if (RefAct == REFRESH){
        RefAct = 0;
        while(!memory->CircularBuffer.empty()){
            result = memory->read();
            cout << "Result : " << result.Value << endl;
            Iter++;
        }
    }
}




void DISPLAY::PrintDISPLAY(){
    cout << "REFRESH: " << REFRESH << endl;
    cout << "SOURCE: " << SOURCE << endl;
}


#endif
