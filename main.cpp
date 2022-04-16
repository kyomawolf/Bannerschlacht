#include <string>
#include <iostream>
#include "board.hpp"
#include <raylib.h>
#include "unit.hpp"


using namespace std;

int main (int argc, char **argv) {
    board* gameBoard = new board(20, 10);
    std::cout << "selected Map 20 x 10: \n";
    gameBoard->printBoard();
}
