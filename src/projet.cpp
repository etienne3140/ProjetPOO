#include <iostream>
#include "CPU.hpp"
#include "BUS.hpp"
#include "MEMORY.hpp"
#include "DISPLAY.hpp"

using namespace std;

int main(){
    CPU cpu1;
    cpu1.load("cpu1.txt");
    BUS bus;
    bus.load("bus1.txt");
    bus.PrintBUS();
    cpu1.simulate();
    bus.simulate(&cpu1);
    bus.read();
    bus.read();
    bus.read();
}


