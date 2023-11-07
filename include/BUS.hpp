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
        queue<double> CircularFifo;
        int ReadTimes;
        DataValue Data;
        CPU cpu;
        void load(const string& fileName);      
        void simulate(CPU *cpu);
        double read();
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
    // connect cpu.data que tu es en train de lire....
    
    int k;
    double result;
    for (k = 0; k < WIDTH; k++){
        
        if (SizeFifo >= WIDTH){
            cout << "Le bus est plein" << endl;
            break;
        }
        cpu->read();
        Data.Value = (cpu->Data).Value;
        Data.ValidityFlag =(cpu->Data).ValidityFlag;
        cout << Data.ValidityFlag << endl;
        cout << Data.Value << endl;
        if (!Data.ValidityFlag){
            break;
        }
        result = Data.Value;
        /*
        result = cpu->registre.ReturnResult();
        cout << "resultat : " << result << endl;
        */
        CircularFifo.push(result);
        SizeFifo++;
        cout << "Taille fifo : " << SizeFifo << endl;
    }
}

double BUS::read(){
    if (!CircularFifo.empty()) {
        SizeFifo--;
        ReadTimes++;
        double result = CircularFifo.front();
        CircularFifo.pop();
        cout << "Resultat lu : " << result << endl;
        return result;
    }
}

void BUS::PrintBusElements(){
    queue<double> copy_fifo = CircularFifo;
    while (!copy_fifo.empty()) {
        cout << copy_fifo.front() << " ";
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