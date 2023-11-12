#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include "CPU.hpp"

using namespace std;

#ifndef BUS_H
#define BUS_H

class BUS {
    private:
        string LABEL;
        int WIDTH;
        string SOURCE;
        int SizeFifo;
    public:
        queue<DataValue> CircularFifo;
        int ReadTimes;
        CPU cpu;
        void load(const string& fileName);      
        void simulate(CPU *cpu);
        DataValue read();
        void PrintBUS();
        void PrintBusElements();
        BUS() :
            LABEL(""),
            WIDTH(0),
            SOURCE(""),
            SizeFifo(0),
            ReadTimes(0)
            {};
};



void BUS::load(const string& fileName) {
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
            if (cle == "LABEL") {                    
                LABEL = value;
            }
            else if (cle == "WIDTH") {
                WIDTH = std::stoi(value); 
            } 
            else if (cle == "SOURCE") {
                SOURCE = value; 
            }
        }
        file.close();
}

void BUS::simulate(CPU *cpu){
    int k;
    //double result;
    DataValue Data;
    for (k = 0; k < WIDTH; k++){
        if (SizeFifo >= WIDTH){
            break;
        }
        
        if (SizeFifo >= WIDTH){
            cout << "Le bus est plein" << endl;
            break;
        }
        cpu->read();
        Data.Value = (cpu->Data).Value;
        Data.ValidityFlag =(cpu->Data).ValidityFlag;
        //cout << Data.ValidityFlag << endl;
        //cout << Data.Value << endl;
        if (!Data.ValidityFlag){
            break;
        }
        CircularFifo.push(Data);
        SizeFifo++;
        //cout << "Taille fifo : " << SizeFifo << endl;
    }
}

DataValue BUS::read(){
    if (!CircularFifo.empty()) {
        SizeFifo--;
        ReadTimes++;
        DataValue result = CircularFifo.front();
        CircularFifo.pop();
        return result;
    }
}

void BUS::PrintBusElements(){
    queue<DataValue> copy_fifo = CircularFifo;
    DataValue result;
    while (!copy_fifo.empty()) {
        result = copy_fifo.front();
        //cout << "Contenu du bus : " << result.ValidityFlag << " " << result.Value << endl;
        copy_fifo.pop();
    }
    cout << endl;
}

void BUS::PrintBUS(){
    cout << "LABEL: " << LABEL << endl;
    cout << "SOURCE: " << SOURCE << endl;
    cout << "WIDTH: " << WIDTH << endl;
}



#endif