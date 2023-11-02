#include <iostream>
#include "CPU.hpp"
#include "BUS.hpp"
#include "MEMORY.hpp"
#include "DISPLAY.hpp"


int main(){
    CPU cpu1;
    cpu1.load("cpu1.txt");
    cpu1.simulate();
}


