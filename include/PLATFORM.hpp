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
    int x = 0;
    while (display.Iter < total || x < 25){
        x++;
        if (x > 25){
            break;
        }
        if (display.Iter >= total){
            break;
        }
        bus.simulate(&cpu);
        for (int i = 0; i<memory.ACCESS; i++){
            memory.simulate(&bus);
        }
        for (int j = 0; j<display.REFRESH; j++){
            display.simulate(&memory);
        }    
    }

}

//5 3.3 15.006 4.2 50 30.3 1500.06 4.02 5 3.3 15.006 4.2 50 30.3 1500.06 4.02 5 3.3 15.006 4.2


#endif
