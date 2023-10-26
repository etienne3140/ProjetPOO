#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef BUS_H
#define BUS_H

class BUS {
    private:
        string LABEL;
        int WIDTH;
        string SOURCE;
    public:
        void load(const string& fileName);      
        void PrintBUS();
        BUS() :
            LABEL(""),
            WIDTH(0),
            SOURCE("")
            {};
};



void BUS::load(const string& fileName) {
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
            else if (cle == "WIDTH") {
                WIDTH = std::stoi(value); 
            } 
            else if (cle == "SOURCE") {
                SOURCE = value; 
            }
        }
        file.close();
}




void BUS::PrintBUS(){
    cout << "LABEL: " << LABEL << endl;
    cout << "SOURCE: " << SOURCE << endl;
    cout << "WIDTH: " << WIDTH << endl;
}



#endif