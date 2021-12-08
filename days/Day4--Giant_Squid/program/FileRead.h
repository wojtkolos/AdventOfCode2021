#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

//
//  file read
//
template <typename T>
class FileOperations {
public:
    static void readToVec(std::string name, std::vector<T>& vect);
    static void vecToFile(std::string name, std::vector<T>& vect);
};

template <typename T>
void FileOperations<T>::readToVec(std::string name, std::vector<T>& vect) {
    std::ifstream file(name);
    if (file.is_open()) {
        std::cout << "File [" << name << "] open" << std::endl;
        while (!file.eof()) {
            T number;
            file >> number;
            vect.push_back(number);
        }
        file.close();
    }
    else {
        std::cout << "Could not open the file" << std::endl;
    }
}

template <typename T>
void FileOperations<T>::vecToFile(std::string name, std::vector<T>& vect) {
    std::ofstream file(name);
    if (file.is_open()) {
        std::cout << "File [" << name << "] open" << std::endl;
        for(auto& board : vect){
            file << "Twoj wynik dla: \n" << board << "to: [" << board.getScore() << "] punkty \n\n";
        }
        file.close();
    }
    else {
        std::cout << "Could not open the file" << std::endl;
    }

}
//
//
//