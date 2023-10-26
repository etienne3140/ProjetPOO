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
        std::ifstream file("data/"+fileName);

        if (!file) {
            std::cerr << "Impossible d'ouvrir le file " << fileName << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(':');
            std::string cle = line.substr(0, pos);
            std::string value = line.substr(pos + 2); 
            if (cle == "LABEL") {                    
                LABEL = value;
            }
            else if (cle == "FREQUENCY") {
                FREQUENCY = std::stoi(value); 
            } 
            else if (cle == "CORES") {
                CORES = std::stoi(value); 
            }
            else if (cle == "PROGRAM"){
                PROGRAM = value;
            }
        }
        file.close();
}



void CPU::PrintCPU(){
    cout << "LABEL: " << LABEL << endl;
    cout << "CORES: " << CORES << endl;
    cout << "FREQUENCY: " << FREQUENCY << endl;
    cout << "PROGRAM: " << PROGRAM << endl;
}


#endif
