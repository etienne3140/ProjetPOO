#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#ifndef MEMORY_H
#define MEMORY_H



class MEMORY {
    private:
        string LABEL;
        int SIZE;
        int ACCESS;
        string SOURCE;
    public:
        void load(const string& fileName);      
        void PrintMEMORY();
        MEMORY() :
            LABEL(""),
            SIZE(0),
            ACCESS(0)
            {};
};



void MEMORY::load(const string& fileName) {
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
            else if (cle == "SIZE") {
                SIZE = std::stoi(value); 
            } 
            else if (cle == "ACCESS") {
                ACCESS = std::stoi(value); 
            }
            else if (cle == "SOURCE"){
                SOURCE = value;
            }
        }
        file.close();
}



void MEMORY::PrintMEMORY(){
    cout << "LABEL: " << LABEL << endl;
    cout << "ACCESS: " << ACCESS << endl;
    cout << "SIZE: " << SIZE << endl;
    cout << "SOURCE: " << SOURCE << endl;
}


#endif
