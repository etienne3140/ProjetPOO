#include <iostream>
#include "CPU.hpp"
#include "BUS.hpp"
#include "MEMORY.hpp"
#include "DISPLAY.hpp"


int main(){
    DISPLAY display;
    display.load("display.txt");
    display.PrintDISPLAY();
}


