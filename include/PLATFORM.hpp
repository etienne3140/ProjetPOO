#include <iostream>
#include <string>
#include "CPU.hpp"
#include "BUS.hpp"
#include "MEMORY.hpp"
#include "DISPLAY.hpp"

using namespace std;

#ifndef PLATFORM_H
#define PLATFORM_H

class PLATFORM{
    private:
        CPU cpu;
        BUS bus;
        MEMORY memory;
        DISPLAY display;
    public:
        void load(const string& fileName);
        void simulate();
};


void PLATFORM::load(const string& fileName) {
        ifstream file("data/"+fileName);
        if (!file) {
            cerr << "Impossible d'ouvrir le file " << fileName << endl;
            return;
        }
        string line;
        getline(file, line);
        cpu.load(line);
        getline(file, line);
        bus.load(line);
        getline(file, line);
        memory.load(line);
        getline(file, line);
        display.load(line);
        file.close();
}


void PLATFORM::simulate(){
    PROGRAMME prgm;
    cpu.simulate();
    prgm.FileName = "data/program.txt";
    prgm.count();
    int total = cpu.iteration;
    cout << endl;
    cout << "total : " << total << endl;
    while (display.Iter < total){
        bus.simulate(&cpu);
        for (int i; i<memory.ACCESS-1; i++){
            memory.simulate(&bus);
            cout << "Empty : " << bus.CircularFifo.empty() << endl;
            bus.PrintBusElements();
        }
        for (int j; j<display.REFRESH; j++){
            display.simulate(&memory);
            memory.PrintMemoryElements();
        }    
    }

}

#endif