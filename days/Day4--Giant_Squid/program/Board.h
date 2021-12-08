#include <iostream>
#include <vector>
#include <string>

//
//  Board
//
class Board {
private:
    std::vector<std::vector<bool>> checked;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> counter;

    bool isBingo;
    int lastNumber;

    int sumOfNotHited();
    bool added;
    friend std::istream& operator>>(std::istream&, Board&);
    friend std::ostream& operator<<(std::ostream&, Board&);
    friend bool operator== (std::vector<Board>&, Board&);
public:
    Board();

    bool bingo(int toCheck);
    unsigned int getScore();

    void setAdded(bool a);
    bool getAdded() { return added; }

    
};