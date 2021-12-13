
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>


std::vector<std::vector<int>> read(std::string fname) {
    std::ifstream file(fname);
    std::vector<std::vector<int>> lines;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream lineStream(line);
            std::vector<int> row;
            char in;
            while (lineStream >> in) {
                row.push_back(in - '0');
            }
            lines.push_back(row);
        }
        file.close();
    }
    return lines;
}

class SmokeBasin {
    public:
        SmokeBasin(std::string fname) {
            lines = read(fname);
            colSize = lines.size();
            rowSize = lines[0].size();
        }

        int calculateSmoke() {
            int sum = 0;
            for (int i = 0; i < colSize; ++i) {
                std::vector<std::pair<bool, int>> line;
                for (int j = 0; j < rowSize; ++j) {
                    line.push_back(std::make_pair(isLowPoint(i, j), lines[i][j]));
                    if(line.back().first) sum += lines[i][j] + 1;
                }
                ans.push_back(line);
            }
            return sum;
        }

        void printAns() {
            for (int i = 0; i < ans.size(); ++i) {
                for (int j = 0; j < ans[i].size(); ++j) {
                    if (ans[i][j].first) {
                        std::cout << "\033[0;95m" << ans[i][j].second << "\033[0m ";
                    }
                    else {
                        std::cout << ans[i][j].second << " ";
                    }
                }
                std::cout << std::endl;
            }
        }

    private:
        bool isLowPoint(int col, int row) {
            int up = (row == 0) ? 10 : lines[col][row - 1],
                left = (col == 0) ? 10 : lines[col - 1][row],

                down = (row == rowSize - 1) ? 10 : lines[col][row + 1],
                right = (col == colSize - 1) ? 10 : lines[col + 1][row];


            if ((lines[col][row] >= up) or   
               (lines[col][row] >= left) or
               (lines[col][row] >= down) or
               (lines[col][row] >= right))
                    return false;
            return true;
        }

        int colSize;
        int rowSize;
        std::vector<std::vector<int>> lines;
        std::vector<std::vector<std::pair<bool, int>>> ans;
};



int main()
{
    SmokeBasin s("data_test.txt");
    std::cout << "\033[0;32m" << s.calculateSmoke() << "\033[0m " << std::endl;

    SmokeBasin s2("data.txt");
    std::cout << "\033[0;32m" << s2.calculateSmoke() << "\033[0m " << std::endl;
    //s.printAns();

    assert(("SmokeBasin [s] obcject for 'data_text.txt' should retrun score: 15", s.calculateSmoke() == 15));
    assert(("SmokeBasin [s2] obcject for 'data.txt' should retrun score: 603", s2.calculateSmoke() == 603));

}
