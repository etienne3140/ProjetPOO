#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "CPU.hpp"
#include "BUS.hpp"

using namespace std;

#ifndef MEMORY_H
#define MEMORY_H



class MEMORY {
    private:
        string LABEL;
        int SIZE;
        string SOURCE;
        int SizeBuffer;
        int AccessTime;
    public:
        int ACCESS;
        queue<DataValue> CircularBuffer;
        void load(const string& fileName);    
        void simulate(BUS* bus);  
        DataValue read();
        void PrintMemoryElements();
        void PrintMEMORY();
        MEMORY() :
            LABEL(""),
            SIZE(0),
            ACCESS(0),
            SizeBuffer(0),
            AccessTime(0)
            {};
};



void MEMORY::load(const string& fileName) {
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
            else if (cle == "SIZE") {
                SIZE = std::stoi(value); 
            } 
            else if (cle == "ACCESS") {
                ACCESS = std::stoi(value); 
            }
            else if (cle == "SOURCE"){
                SOURCE = value;
            }
        }
        file.close();
}

void MEMORY::simulate(BUS *bus){
    int k;
    DataValue result;
    AccessTime++;
    cout << "A : " << AccessTime << endl;
    if (AccessTime == ACCESS){
        AccessTime = 0;
        while(!bus->CircularFifo.empty()){
            if (SizeBuffer >= SIZE){
                cout << "Le bus est plein" << endl;
                break;
            }
            result = bus->read();
            cout << "cool" << endl;
            bus->PrintBusElements();
            if (!result.ValidityFlag){
                break;
            }
            CircularBuffer.push(result);
        }
    }
}

DataValue MEMORY::read(){
    if (!CircularBuffer.empty()) {
        SizeBuffer--;
        DataValue result = CircularBuffer.front();
        CircularBuffer.pop();
        return result;
    }
}

void MEMORY::PrintMemoryElements(){
    queue<DataValue> copy_fifo = CircularBuffer;
    DataValue result;
    while (!copy_fifo.empty()) {
        result = copy_fifo.front();
        cout << "Contenu de la mémoire : " << result.ValidityFlag << " " <<  result.Value << endl;
        copy_fifo.pop();
    }
    cout << endl;
}


void MEMORY::PrintMEMORY(){
    cout << "LABEL: " << LABEL << endl;
    cout << "ACCESS: " << ACCESS << endl;
    cout << "SIZE: " << SIZE << endl;
    cout << "SOURCE: " << SOURCE << endl;
}


#endif
