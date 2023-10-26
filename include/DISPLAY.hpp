#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef DISPLAY_H
#define DISPLAY_H



class DISPLAY {
    private:
        int REFRESH;
        string SOURCE;
    public:
        void load(const string& fileName);      
        void PrintDISPLAY();
        DISPLAY() :
            REFRESH(0),
            SOURCE("")
            {};
};



void DISPLAY::load(const string& fileName) {
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
            if (cle == "REFRESH") {
                REFRESH = std::stoi(value); 
            } 
            else if (cle == "SOURCE"){
                SOURCE = value;
            }
        }
        file.close();
}



void DISPLAY::PrintDISPLAY(){
    cout << "REFRESH: " << REFRESH << endl;
    cout << "SOURCE: " << SOURCE << endl;
}


#endif