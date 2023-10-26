#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef CPU_H
#define CPU_H



class CPU {
    private:
        string LABEL;
        int FREQUENCY;
        int CORES;
        string PROGRAM;
        int CurrentlyActiveCores;
    public:
        void load(const string& fileName);      
        void PrintCPU();
        CPU() :
            LABEL(""),
            FREQUENCY(0),
            CORES(0),
            CurrentlyActiveCores(0)
            {};
};



void CPU::load(const string& fileName) {
        std::ifstream fichier("data/"+fileName);

        if (!fichier) {
            std::cerr << "Impossible d'ouvrir le fichier " << fileName << std::endl;
            return;
        }

        std::string ligne;
        while (std::getline(fichier, ligne)) {
            size_t pos = ligne.find(':');
            std::string cle = ligne.substr(0, pos);
            std::string valeur = ligne.substr(pos + 2); // +2 pour sauter ": "
            if (cle == "LABEL") {                    
                LABEL = valeur;
            }
            else if (cle == "FREQUENCY") {
                FREQUENCY = std::stod(valeur); // Convertit la chaîne en double
            } 
            else if (cle == "CORES") {
                CORES = std::stoi(valeur); // Convertit la chaîne en int
            }
            else if (cle == "PROGRAM"){
                PROGRAM = valeur;
            }
        }
        fichier.close();
}



void CPU::PrintCPU(){
    cout << "LABEL: " << LABEL << endl;
    cout << "CORES: " << CORES << endl;
    cout << "FREQUENCY: " << FREQUENCY << endl;
    cout << "PROGRAM: " << PROGRAM << endl;
}


#endif
