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
        int CurrentlyActiveCores;
    public:
        string PROGRAM;
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
        ifstream file("data/"+fileName);

        if (!file) {
            cerr << "Impossible d'ouvrir le file " << fileName << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            size_t pos = line.find(':');
            string cle = line.substr(0, pos);
            string value = line.substr(pos + 2); 
            if (cle == "LABEL") {                    
                LABEL = value;
            }
            else if (cle == "FREQUENCY") {
                FREQUENCY = stoi(value); 
            } 
            else if (cle == "CORES") {
                CORES = stoi(value); 
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
