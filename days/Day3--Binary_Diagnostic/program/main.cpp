

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>

void fileRead(std::string fname, std::vector<std::string>& vec) {
    std::ifstream file(fname);
    if (file.is_open()) {
        std::cout << "File [" << fname << "] open" << std::endl;
        std::string line;
        while (file >> line) {
            vec.push_back(line);
        }

    }
    else {
        std::cout << "couldn\'t open file!";
    }
}


class BinaryDiagnostic {
public:
    BinaryDiagnostic(std::string fname) {
        fileRead(fname, lines);
    }

    std::string advantagePick(std::vector<short int>& ones, std::vector<short int>& zeros) {
        std::string binary;
        for (int i = 0; i < ones.size(); ++i) {
            binary += (ones[i] > zeros[i]) ? "1" : "0";
        }
        return binary;
    }

    std::string calculateInDeep() {
        std::vector<short int> ones(lines[0].size(),0);
        std::vector<short int> zeros(lines[0].size(), 0);

        for (auto line : lines) {
            for (auto i = 0; i < line.size(); ++i) {
                (line[i] == '1')? ++ones[i] : ++zeros[i];
            }
        }
        return advantagePick(ones, zeros);
    }

    int calculateScore() {
        std::string binary = calculateInDeep();
        std::string binaryNegation;
        for (auto& el : binary) {
            binaryNegation += (el == '1')? "0" : "1";
        }


        int number = std::stoi(binary, 0, 2);
        int numberNegation = std::stoi(binaryNegation, 0, 2);
        return number * numberNegation;
    }

    std::string binaryFilter(char symb) {
        std::vector<std::string> filter(lines);
        for (auto i = 0; i < filter[0].size() && filter.size() > 1 ; ++i) {
            std::array<std::vector<std::string>, 2> filtered;
            for (auto& line : filter) {
                try {
                    (line[i] == symb) ? filtered[1].push_back(line) : filtered[0].push_back(line);
                }
                catch (...) {
                    std::cout << "Error: ";
                }
            }
            if (symb == '1')
                filter = (filtered[0].size() > filtered[1].size()) ? filtered[0] : filtered[1];
            else
                if ((filtered[0].size() > filtered[1].size()) or (filtered[0].size() == filtered[1].size())) filter = filtered[1];
                else 
                    filter = filtered[0];
        }
        return filter[0];
    }

    unsigned int advantagePick2() {
        std::string ox = binaryFilter('1');
        std::string co = binaryFilter('0');
        unsigned int oxygen = std::stoi(ox, 0, 2);
        unsigned int co2 = std::stoi(co, 0, 2);

        return oxygen * co2;
    }

private:
    std::vector<std::string> lines;
    
};



int main()
{
    BinaryDiagnostic d1("data.txt");
    
    std::cout << d1.calculateScore() << std::endl;
    std::cout << d1.advantagePick2() << std::endl;

    return 0;
}





