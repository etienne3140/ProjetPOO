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
        void PrintRegister();
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

void REGISTER::PrintRegister(){
    queue<double> copy_fifo = fifo;
     while (!copy_fifo.empty()) {
        cout << copy_fifo.front() << " ";
        copy_fifo.pop();
    }
    cout << endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~Création du programme~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class PROGRAMME {
    public :
        string FileName;
        string program;
        int ActualLine;
        void load();
        double compute();
        PROGRAMME() :
            ActualLine(0),
            program(""),
            FileName("data/"+program)
            {};
};

void PROGRAMME::load(){
    REGISTER registre;

}

double PROGRAMME::compute(){
    ifstream file(FileName);
    if (!file) {
        cout << program << endl;
        cerr << "Impossible d'ouvrir le fichier " << program << endl;
        return 0;
    }
    string ope, nb1, nb2;
    string line;
    int i = 0;
    while(getline(file, line)){
        if (i == ActualLine){
            istringstream operators(line);
            operators >> ope >> nb1 >> nb2;
            break;
        }
        i++;

    }
    ActualLine++;
    double a;
    if (ope == "NOP"){
        a = 0;
        cout << "NOP " << a << endl;
        return a;
    }
    else if (ope == "ADD"){
        a = stod(nb1)+stod(nb2);
        cout << "ADD " << a << endl;
        return a;
    }
    else if(ope == "SUB"){
        a = stod(nb1)-stod(nb2);
        cout << "SUB " << a << endl;
        return a;
    }
    else if(ope == "MUL"){
        a = stod(nb1)*stod(nb2);
        cout << "MUL " << a << endl;
        return a;
    }
    else if (ope == "DIV"){
        a = stod(nb1)/stod(nb2);
        cout << "DIV " << a << endl;
        return a;
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
        REGISTER registre;
        PROGRAMME programme;
    public:
        void load(const string& fileName);      
        void PrintCPU();
        void simulate();
        CPU() :
            LABEL(""),
            FREQUENCY(0),
            CORES(0),
            CurrentlyActiveCores(0)
            {};
};



void CPU::load(const string& fileName){
    programme.load();
    ifstream file("data/"+fileName);
    if (!file) {
        cerr << "Impossible d'ouvrir le fichier " << fileName << endl;
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
            programme.FileName = value; //Ajout nom du fichier program dans la classe PROGRAM
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

void CPU::simulate(){
    int cores = 0;
    while (cores < CORES){
        cout << "ok1" << endl;
        int F = 0;
        cores++;
        while (F < FREQUENCY){
            cout << "ok2" << endl;
            F++;
            //programme.compute();
            registre.AddResult(programme.compute());
        }
        CurrentlyActiveCores++;
    }
    registre.PrintRegister();
}

#endif
