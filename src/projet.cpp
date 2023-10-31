#include <iostream>
#include "CPU.hpp"
#include "BUS.hpp"
#include "MEMORY.hpp"
#include "DISPLAY.hpp"
#include "REGISTER.hpp"

int main(){
    REGISTER registre;
    
    registre.AddResult(12.53);
    registre.AddResult(1.62);
    registre.AddResult(543.482);

    while (!registre.fifo.empty()) {
        double resultat = registre.ReturnResult();
        cout << "Résultat du registre : " << resultat << endl;
    }

    return 0;
}


