#include <iostream>
#include <vector>
#include <array>
#include <regex>
#include <string>
#include <fstream>
#include <utility>
#include <map>

struct Point {
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
    int x;
    int y;
};

bool operator<(const Point& p1, const Point& p2)
{
    return p1.x == p2.x && p1.y < p2.y || p1.x < p2.x;
}

class Line {
public:
    Line(std::array<int, 4> arr) {
        if (arr[0] > arr[2])
            std::swap(arr[0], arr[2]);
        if (arr[1] > arr[3])
            std::swap(arr[1], arr[3]);

        points = std::make_pair(Point{ arr[0], arr[1] }, Point{ arr[2], arr[3] });
    }

    int& operator[](unsigned short i) {
        switch (i)
        {
        case 0: return points.first.x;
        case 1: return points.first.y;
        case 2: return points.second.x;
        case 3: return points.second.y;
        }
    }
    bool isVertical() const { return points.first.y == points.second.y; }
    bool isHorizontal() const { return points.first.x == points.second.x; }
    bool diagonal1() const { return points.first.x < points.second.x && points.first.y < points.second.y; }
    bool diagonal2() const { return points.first.x > points.second.x && points.first.y < points.second.y; }
    bool diagonal3() const { return points.first.x < points.second.x && points.first.y > points.second.y; }
    bool diagonal4() const { return points.first.x > points.second.x && points.first.y > points.second.y; }

private:
    std::pair<Point, Point> points;

};


std::array<int, 4>& regexLineFilter(std::string line) {
    std::string regexPattern("[0-9]+");
    std::regex reg(regexPattern, std::regex::icase);
    unsigned short index = 0;
    std::array<int, 4> arr;
    for (std::sregex_iterator it(line.begin(), line.end(), reg), end_it; it != end_it && index < 4; ++it) {
        arr[index++] = std::stoi(it->str());
    }
    return arr;
}

std::vector<Line> readFile(std::string fname) {
    std::ifstream file(fname);
    if (file.is_open()) {
        std::string strLine;
        std::vector<Line> vec;
       
        while (std::getline(file, strLine)) { 
            vec.push_back(Line(regexLineFilter(strLine)));
        }
        return vec;
    }
    else 
        std::cout << "couldn\' open the " << fname << std::endl;
}


class HydrotermalVenture {
    public:
        HydrotermalVenture(std::string fname)
            : maxSize(0) 
        {
            lines = readFile(fname);
        }

        void searchForPoint(Point p, std::map<Point, int>& map) {
                auto it = map.find(p);
                (it != map.end()) ?
                    it->second++ : map[p] = 1;
        }

        int calculateThermalVents() {

            std::map<Point, int> map;
            for (auto& line : lines) {
                if (line.isHorizontal()) {
                    for (int y = line[1]; y <= line[2]; y++) {
                        searchForPoint(Point{ line[0], y }, map);
                    }

                }
                else if (line.isVertical()) {
                    for (int x = line[0]; x <= line[2]; x++) {
                        searchForPoint(Point{ x, line[1] }, map);
                    }
                }
            }
            int ans = std::count_if(map.begin(), map.end(), [](auto&& p) { return p.second >= 2; });

            return ans;
        }


        int calculateThermalVents2() {

            std::map<Point, int> map;
            for (auto& line : lines) {
                if (line.isHorizontal()) {
                    for (int y = line[1]; y <= line[2]; y++) {
                        searchForPoint(Point{ line[0], y }, map);
                    }
                    
                }
                else if (line.isVertical()) {
                    for (int x = line[0]; x <= line[2]; x++) {
                        searchForPoint(Point{ x, line[1] }, map);
                    }
                }
                else if (line.diagonal1()) {
                    for (int x = line[0], y = line[1]; x <= line[2]; x++, y++) {
                        searchForPoint(Point{ x, y }, map);
                    }
                }
                else if (line.diagonal2()) {
                    for (int x = line[0], y = line[1]; x >= line[2]; x--, y++) {
                        searchForPoint(Point{ x, y }, map);
                    }
                }
                else if (line.diagonal3()) {
                    for (int x = line[0], y = line[1]; x <= line[2]; x++, y--) {
                        searchForPoint(Point{ x, y }, map);
                    }
                }
                else if (line.diagonal4()) {
                    for (int x = line[0], y = line[1]; x >= line[2]; x--, y--) {
                        searchForPoint(Point{ x, y }, map);
                    }
                }
            }
            int ans = std::count_if(map.begin(), map.end(), [](auto&& p) { return p.second >= 2; });
                
            return ans;
        }

    private:
        std::vector<Line> lines;
        int maxSize;
};



int main()
{
    HydrotermalVenture hv("data.txt");
    std::cout << hv.calculateThermalVents() << std::endl;
    HydrotermalVenture hv2("data2.txt");
    std::cout << hv2.calculateThermalVents2() << std::endl;

}
