#include <iostream>
#include "CPU.hpp"
#include "BUS.hpp"
#include "MEMORY.hpp"
#include "DISPLAY.hpp"
#include "PLATFORM.hpp"

using namespace std;

int main(){
    /*
    CPU cpu1;
    cpu1.load("cpu1.txt");
    BUS bus;
    MEMORY memory;
    memory.load("mem1.txt");
    DISPLAY display;
    display.load("display.txt");
    bus.load("bus1.txt");
    bus.PrintBUS();
    cpu1.simulate();
    bus.simulate(&cpu1);
    bus.PrintBusElements();
    
    memory.simulate(&bus);
    memory.simulate(&bus);
    memory.simulate(&bus);
    memory.PrintMemoryElements();
    /*
    bus.simulate(&cpu1);
    memory.simulate(&bus);
    //memory.read();
    memory.PrintMemoryElements();
    
    display.simulate(&memory);
    display.simulate(&memory);
    display.simulate(&memory);
    display.simulate(&memory);
    display.simulate(&memory);
    display.simulate(&memory);
    display.simulate(&memory);
    display.simulate(&memory);
    */
    
   PLATFORM platform;
   platform.load("platform.txt");
   platform.simulate();
    
}


