
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>


void fileRead(std::string fname, std::vector<std::pair<std::string, int>>& vec) {
    std::ifstream file(fname);
    if (file.is_open()) {
        std::cout << "File [" << fname << "] open" << std::endl;
        std::string line;
        int num = 0;       
        while (file >> line >> num) {
            vec.push_back(std::make_pair(line, num));
        }
    }
    else {
        std::cout << "couldn\'t open file!";
    }
}


class SubmarineMove {
    public:
        SubmarineMove(std::string fname) 
        {
            fileRead(fname, vec);
        }

        int calculatePos() {
            long long int horizontal = 0;
            long long int depth = 0;
            long long int aim = 0;
            for (auto elem : vec) {
                if (elem.first == "forward") {
                    horizontal += elem.second;
                }
                else if (elem.first == "down") {
                    depth += elem.second;
                }
                else if (elem.first == "up") {
                    depth -= elem.second;
                }
            }
            return horizontal * depth;
        }

        long long int calculatePos2() {
            long long int horizontal = 0;
            long long int depth = 0;
            long long int aim = 0;
            for (auto elem : vec) {
                if (elem.first == "forward") {
                    horizontal += elem.second;
                    depth += aim * elem.second;
                }
                else if (elem.first == "down") {
                    aim += elem.second;
                }
                else if (elem.first == "up") {
                    aim -= elem.second;
                }
            }
            return horizontal * depth;
        }

        

    private:
        std::vector<std::pair<std::string, int>> vec;
        
};



int main()
{
    SubmarineMove sb("data.txt");
    std::cout << sb.calculatePos() << std::endl;
    std::cout << sb.calculatePos2() << std::endl;
}
