#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>



std::vector<std::string> readFile(std::string fname) {
    std::vector<std::string> vec;
    std::ifstream file(fname);
    if (file.is_open()) {
        std::string temp;
        while (std::getline(file, temp)) {
            std::size_t delimiter = temp.find('|');
            //std::stringstream before(temp.substr(0, delimiter));
            std::stringstream after(temp.substr(delimiter + 2));

            while (after >> temp) {
                vec.emplace_back(temp);
            }

        }

        return vec;
    }
}

    class SevenSegmentSearch {
    public:
        SevenSegmentSearch(std::string fname) {
            lines = readFile(fname);
        }

        int calculateSegm() {
            int counter = 0;
            for (auto& line : lines) {
                switch (line.size()) {
                case 2:;
                case 4:;
                case 3:;
                case 7: {
                    counter++;
                    break;
                }
                }
            }
            return counter;
        }
    private:
        std::vector<std::string> lines;
    };



int main()
{
    SevenSegmentSearch s("data.txt");
    std::cout << s.calculateSegm() << std::endl;
}
