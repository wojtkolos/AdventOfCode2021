#include <fstream>
#include<algorithm>
#include <iterator>
//#include <numeric>


#include "Board.h"
#include "FileRead.h"





//
//  display score - debug
//
template <typename T>
void disp(std::vector<T>& vect) {
    for (auto& i : vect) {
        std::cout << i << std::endl;
    }
}
//
//
//


#include "BingoController.h"

int main() {
    
    BingoController controller("numbers.txt", "boards.txt");
    
    controller.checkBoardsForBingo();
    controller.displayBingoBoardsScores();
    controller.saveBingoBoardsScores();
}

