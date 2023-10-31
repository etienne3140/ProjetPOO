#include <iostream>
#include "CPU.hpp"
#include "BUS.hpp"
#include "MEMORY.hpp"
#include "DISPLAY.hpp"



ifstream file("data/program.txt");

void computing(){
    if (!file) {
        cerr << "Impossible d'ouvrir le fichier " << "program.txt" << endl;
        return;
    }
    string ope, nb1, nb2;
    file >> ope >> nb1 >> nb2;
    cout << ope << endl;
    cout << nb1 << endl;
    cout << nb2 << endl;
}

int main(){
    computing();
    computing();
}


