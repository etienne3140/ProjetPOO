#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

#ifndef CPU_H
#define CPU_H

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~Création de la DataValue~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class DataValue{
    public:
        bool ValidityFlag;
        double Value;
        DataValue(): ValidityFlag(0), Value(0.0){};
        DataValue(bool val, double v): ValidityFlag(val), Value(v){};
    };


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~Création du registre~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class REGISTER {
    private :
        //double value;
    public :
        queue<DataValue> fifo;
        void AddResult(DataValue result);
        DataValue ReturnResult();
        void PrintRegister();
        //REGISTER() :
            //value(0)
        //    {};
};

void REGISTER::AddResult(DataValue result){
    fifo.push(result);
}

DataValue REGISTER::ReturnResult(){
    if (!fifo.empty()) {
        DataValue result = fifo.front();
        fifo.pop();
        return result;
    }
    DataValue empty;
    empty.ValidityFlag = 0;
    empty.Value = 12;
    return empty;
}

void REGISTER::PrintRegister(){
    queue<DataValue> copy_fifo = fifo;
     while (!copy_fifo.empty()) {
        cout << copy_fifo.front().ValidityFlag << endl;
        cout << copy_fifo.front().Value << endl;
        copy_fifo.pop();
    }
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
        return a;
    }
    else if (ope == "ADD"){
        a = stod(nb1)+stod(nb2);
        return a;
    }
    else if(ope == "SUB"){
        a = stod(nb1)-stod(nb2);
        return a;
    }
    else if(ope == "MUL"){
        a = stod(nb1)*stod(nb2);
        return a;
    }
    else if (ope == "DIV"){
        a = stod(nb1)/stod(nb2);
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
        PROGRAMME programme;
    public:
        DataValue Data;
        REGISTER registre;
        int iteration;
        void read();
        void load(const string& fileName);      
        void PrintCPU();
        void simulate();
        CPU() :
            LABEL(""),
            FREQUENCY(0),
            CORES(0),
            CurrentlyActiveCores(0),
            iteration(0)
            {};
    };

void CPU::read(){
    if (registre.fifo.empty()){
        Data.ValidityFlag = 0;
        Data.Value = 12;
    }
    Data = registre.fifo.front();
    registre.fifo.pop();
}


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
    iteration = FREQUENCY*CORES;
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
    DataValue test;
    int cores = 0;
    while (cores < CORES){
        int F = 0;
        cores++;
        while (F < FREQUENCY){
            F++;
            if (programme.ActualLine == programme.NbLignes-1){
                test.Value = programme.compute();
                test.ValidityFlag = 1;
                registre.AddResult(test);
                programme.ActualLine = 0;
                break;
            }
            test.Value = programme.compute();
            test.ValidityFlag = 1;
            registre.AddResult(test);
        }
        CurrentlyActiveCores++;
    }
    //registre.PrintRegister();
}

#endif
