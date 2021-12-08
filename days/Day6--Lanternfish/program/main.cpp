#include <iostream>
#include <array>
#include <vector>
#include <numeric>

#define DATA "data.txt"

using lli = long long int;

class Lanternfish {
    public:
        Lanternfish() {
            fish_population = {
                #include DATA
            };

        }

        long long int process(int days) {
            std::array<lli, 9> counts{};

            for (int i : fish_population) {
                ++counts[i];
            }

            //for (int i = days; i > 0; --i) {
            //    counts[(i + 7) % 9] += counts[i % 9];
            //}

            for(auto i = days; i > 0; --i){
                lli firstIndex = counts[0];
                for (int index = 1; index < 9; index++) {
                    counts[index - 1] = counts[index];
                }
                counts[6] += firstIndex;
                counts[8] = firstIndex;
            }
            lli base = 0;
            return std::accumulate(counts.begin(), counts.end(), base);
        };

    private:
        std::vector<int> fish_population;
};

int main()
{
    Lanternfish l;

    std::cout << l.process(80) << std::endl;
    std::cout << l.process(256) << std::endl;

}

