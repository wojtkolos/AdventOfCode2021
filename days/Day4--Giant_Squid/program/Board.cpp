#include "Board.h"

Board::Board() {
    board.resize(5, std::vector<int>(5, 0));
    checked.resize(5, std::vector<bool>(5, 0));
    counter.resize(2, std::vector<int>(5, 0));
    isBingo = false;
    lastNumber = 0;
    added = false;

}

unsigned int Board::getScore() {
    return this->sumOfNotHited() * lastNumber;
}

int Board::sumOfNotHited() {
    int sum = 0;
    for (int i = 0; i < this->board.size(); ++i) {
        for (int j = 0; j < this->board[i].size(); ++j) {
            if (!this->checked[i][j]) {
                sum += this->board[i][j];
            }
        }
    }
    return sum;
}

void Board::setAdded(bool a) {
    added = a;
}

bool Board::bingo(int toCheck) {
    if (this->isBingo) return true;
    for (int i = 0; i < this->board.size(); ++i) {
        for (int j = 0; j < this->board[i].size(); ++j) {
            if (toCheck == this->board[i][j]) {
                this->checked[i][j] = true;
                this->counter[0][j] += 1;
                this->counter[1][i] += 1;
                if (this->counter[0][j] == 5 or this->counter[1][i] == 5) {
                    this->isBingo = true;
                    this->lastNumber = toCheck;
                    return true;
                }
            }

        }
    }
    return false;
}

std::istream& operator>>(std::istream& input, Board& b) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            input >> b.board[i][j];
        }
    }
    return input;
}

std::ostream& operator<<(std::ostream& input, Board& b) {
    std::string temp;
    for (int i = 0; i < b.board.size(); ++i) {
        for (int j = 0; j < b.board[i].size(); ++j) {
            temp += std::to_string(b.board[i][j]) + " ";
        }
        temp += "\n";
    }
    return input << temp;
}
//
//
//