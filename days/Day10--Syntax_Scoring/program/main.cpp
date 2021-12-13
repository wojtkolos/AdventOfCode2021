
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <cassert>

#define ulli unsigned long long int

std::vector<std::string> read(std::string fname) {
    std::ifstream file(fname);
    std::vector<std::string> vec;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            vec.push_back(line);
        }

        file.close();
    }
    return vec;
}




class SyntaxScoring{
public:
    SyntaxScoring(std::string fname) {
        lines = read(fname);
        points = 0;
    }

    ulli calculatePoints() {
        points = 0;
        for (auto& line : lines) {
            std::string expected;
           
            bool incorrectFirst = false;
            for (char& c : line) {
                
                if (c == '[') {
                    expected.push_back(']');
                }
                else if (c == '{') {
                    expected.push_back('}');
                }
                else if (c == '<') {
                    expected.push_back('>');
                }
                else if (c == '(') {
                    expected.push_back(')');
                }
                else if (c == expected.back()) {
                    expected.pop_back();
                }
                else {
                    points += (c == ')') ? 3 : (c == ']')? 57 : (c == '}') ? 1197 : (c == '>') ? 25137 : 0;
                    incorrectFirst = true;
                    break;
                }
                if (incorrectFirst) continue;
                //{']', 57}, { '}', 1197 }, { '>', 25137 }, { ')', 3 }
            }
        }
        return points;
    }
private:
    std::vector<std::string> lines;
    ulli points;
};


int main()
{
    SyntaxScoring s("data_example.txt");
    std::cout << s.calculatePoints() << std::endl;
    assert(("SyntaxScoring [s] for 'data_example.txt' should be equal == 26397", s.calculatePoints() == 26397));

    SyntaxScoring s2("data.txt");
    std::cout << s2.calculatePoints() << std::endl;
    assert(("SyntaxScoring [s2] for 'data.txt' should be equal == 388713", s2.calculatePoints() == 388713));
}
