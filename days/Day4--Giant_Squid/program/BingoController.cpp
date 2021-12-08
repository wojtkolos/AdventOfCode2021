#include "BingoController.h"
#include "Board.h"


BingoController::BingoController(std::string fnumbers, std::string fboards) {
    FileOperations<int>::readToVec(fnumbers, numbers);
    FileOperations<Board>::readToVec(fboards, boards);
    
}


void BingoController::checkBoardsForBingo() {
    for (auto& i : this->numbers) {
        for (auto& j : this->boards) {
            if (j.bingo(i)) {
                if (!(j.getAdded())) {
                    j.setAdded(true);
                    scoreBoards.push_back(j);
                }
            }
        }
    }
}

void BingoController::displayBingoBoardsScores() {
    if (scoreBoards.empty()) std::cout << "Nie znaleziono bingo :/";
    else {
        for (auto& board : scoreBoards) {
            std::cout << "Twoj wynik dla:" << std::endl <<
                "----------------" << std::endl <<
                board << "to: [" << board.getScore() << "] punkty" << std::endl <<
                "----------------" << std::endl;
        }
    }
}

void BingoController::saveBingoBoardsScores() {
    if (scoreBoards.empty()) std::cout << "Nie znaleziono bingo :/";
    else {
        FileOperations<Board>::vecToFile("bingoBoards.txt", boards);
    }
}

