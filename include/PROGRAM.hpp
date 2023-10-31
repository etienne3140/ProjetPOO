#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "CPU.hpp"

using namespace std;

#ifndef PROGRAM_H
#define PROGRAM_H

class PROGRAM : private CPU{
    private :
        string program;
    public :
        string line;
        void load();
        void compute();
};

void PROGRAM::load(){
    PROGRAM::program = CPU::PROGRAM;
}

void PROGRAM::compute(){
    //getline(program, line);
}

#endif
