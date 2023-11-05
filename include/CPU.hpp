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
        int NbLignes;
        int ActualLine;
        void load();
        void count();
        double compute();
        PROGRAMME() :
            NbLignes(0),
            ActualLine(0),
            program(""),
            FileName("")
            {};
};


void PROGRAMME::load(){
    REGISTER registre;
}

void PROGRAMME::count(){
    //FileName = program;
    cout << "fichier : " << FileName << endl;
    ifstream File(FileName);
    string line;
    while(getline(File, line)){
        NbLignes++;
    }
    File.close();
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
//~~~~~Création de la DataValue~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class DataValue{
    public:
        bool ValidityFlag;
        double Value;
};

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
        DataValue Data;
        void read();
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

void CPU::read(){
    if (registre.fifo.empty()){
        Data.ValidityFlag = 0;
        Data.Value = 12;
    }
    Data.ValidityFlag = 1;
    Data.Value = registre.fifo.front();
    registre.fifo.pop();
//Suite pour le test à enlever
    cout << "Validity : " << Data.ValidityFlag << endl;
    cout << Data.Value << endl;
    registre.PrintRegister();
}


void CPU::load(const string& fileName){
    Data.ValidityFlag = 0;
    Data.Value = 12;
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
    programme.count();
    file.close();
}



void CPU::PrintCPU(){
    cout << "LABEL: " << LABEL << endl;
    cout << "CORES: " << CORES << endl;
    cout << "FREQUENCY: " << FREQUENCY << endl;
    cout << "PROGRAM: " << PROGRAM << endl;
}

void CPU::simulate(){
    double test;
    int cores = 0;
    cout << "coeur tot : " << CORES << endl;
    while (cores < CORES){
        int F = 0;
        cores++;
        while (F < FREQUENCY){
            F++;
            cout << "coeur : " << cores << endl;
            cout << "Actuel : " << programme.ActualLine << endl;
            cout << "Tot : " << programme.NbLignes << endl;
            if (programme.ActualLine == programme.NbLignes-1){
                
                test = programme.compute();
                cout << "test : " << test << endl;
                if (abs(test) > 0.00000000000000001){
                    registre.AddResult(test);
                }
                programme.ActualLine = 0;
                break;
            }
            test = programme.compute();
            if (abs(test) > 0.00000000000000001){
                registre.AddResult(test);
            }
            
        }
        CurrentlyActiveCores++;
    }
    registre.PrintRegister();
}

#endif
