#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include "CPU.hpp"

using namespace std;

#ifndef REGISTER_H
#define REGISTER_H

class REGISTER : public CPU{
    public :
        queue<double> fifo;
        void AddResult(double result);
        double ReturnResult();
};


void REGISTER::AddResult(double result){
    fifo.push(result);
}

double REGISTER::ReturnResult(){
    if (!fifo.empty()) {
        double result = fifo.front();
        fifo.pop();
        return result;
    }
    return 0;
}


#endif
