#include <iostream>
#include <vector>
#include <vector>
#include <fstream>
#include <numeric>

using ush = unsigned short;

void fileRead(std::string fname, std::vector<ush>& vec) {
    std::ifstream file(fname);
    if (file.is_open()) {
        std::cout << "open" << std::endl;
        while (!file.eof()) {
            ush number = 0;
            file >> number;
            vec.push_back(number);
        }
        file.close();
    }
    else 
        std::cout << "couldn\'t open" << std::endl;
}

ush sonarSweep(std::vector<ush>& vec) {
    ush counter = 0;
    ush prevLow = vec.front();
    for (auto mec : vec)
    {
        if (prevLow < mec) {
            prevLow = mec;
            ++counter;
            std::cout << mec << " (increased)" << std::endl;
        }
        else if (prevLow > mec) {
            prevLow = mec;
            std::cout << mec << " (decreased)" << std::endl;
        }
    }
    return counter;
}

ush sonarSweepv2(std::vector<ush>& vec) {
    ush counter = 0;
    for (ush i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[i - 1]) {
            ++counter;
        }
    }
    return counter;
}

ush sonarSweep2(std::vector<ush>& vec) {
    ush counter = 0;
    ush prevLowSum = 0;
    for (auto i = 0; i < vec.size() - 3; ++i)
    {
        ush sum = vec[i];
        ush count = 1;
        for (auto j = i + 1; j < vec.size(); ++j) {
            sum += vec[j];
            ++count;
            if (count == 3) break;
        }
        if (prevLowSum == 0) prevLowSum = sum;
        else if (prevLowSum < sum) {
            prevLowSum = sum;
            ++counter;
            std::cout << sum << " (increased)" << std::endl;
        }
        else if (prevLowSum > sum) {
            prevLowSum = sum;
            std::cout << sum << " (decreased)" << std::endl;
        }
    }
    return counter;
}

ush sonarSweepUniversal(std::vector<ush>& vec, ush num) {
    return std::inner_product(std::begin(vec), std::end(vec) - num, std::begin(vec) + num, 0, std::plus<>(), std::less<int>());
}

int main()
{
    std::vector<ush> measurements;
    fileRead("data.txt", measurements);
    std::cout << sonarSweep(measurements) << std::endl;
    std::cout << sonarSweepv2(measurements) << std::endl;
    std::cout << sonarSweep2(measurements) << std::endl;
    std::cout << sonarSweepUniversal(measurements,3) << std::endl;
}

