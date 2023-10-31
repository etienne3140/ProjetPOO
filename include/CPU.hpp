#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

#ifndef CPU_H
#define CPU_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~Création du registre~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class REGISTER {
    private :
        double value;
    public :
        queue<double> fifo;
        void AddResult(double result);
        double ReturnResult();
        REGISTER() :
            value(0)
            {};
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~Création du programme~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class PROGRAMME {
    private :
        ifstream file;
    public :
        string program;
        void load();
        double compute();
        PROGRAMME() :
            program(""),
            file("data/"+program)
            {};
};

void PROGRAMME::load(){
    REGISTER registre;

}

double PROGRAMME::compute(){
    if (!file) {
        cerr << "Impossible d'ouvrir le fichier " << program << endl;
        return 0;
    }
    string ope, nb1, nb2;
    file >> ope >> nb1 >> nb2;
    if (ope == "NOP"){
        return 0;
    }
    else if (ope == "ADD"){
        return stod(nb1)+stod(nb2);
    }
    else if(ope == "SUB"){
        return stod(nb1)-stod(nb2);
    }
    else if(ope == "MUL"){
        return stod(nb1)*stod(nb2);
    }
    else if (ope == "DIV"){
        return stod(nb1)/stod(nb2);
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~Création du CPU~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
    PROGRAMME program;
    program.load();
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
            program.program = value; //Ajout nom du fichier program dans la classe PROGRAM
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
