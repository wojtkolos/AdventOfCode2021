#pragma once
#include <string>

#include "FileRead.h"

class Board;

class BingoController {
public:
    BingoController(std::string fnumbers, std::string fboards);

    void checkBoardsForBingo();
    void displayBingoBoardsScores();
    void saveBingoBoardsScores();

private:
    bool bingo = false;
    std::vector<Board> boards;
    std::vector<Board> scoreBoards;
    std::vector<int> numbers;
};
