#include <string>
#include <iostream>
#include "board.hpp"
#include "unit.hpp"
#include "main.hpp"
#include "raylib.h" //using version 4.0

import crystal.core;

using namespace std;

void    mainloop(crystal::window *gamewindow, board *gameBoard);

int main (int argc, char **argv) {
    board* gameBoard = new board(20, 10);
    crystal::window *gamewindow = new crystal::window(1920, 1080, "Die Schlacht");
    cout << "selected Map 20 x 10: \n";
    gameBoard->printBoard();
    gamewindow->set_target_fps(60);
    mainloop(gamewindow, gameBoard);
    delete gamewindow;
}

void    mainMenuWindow(crystal::window *gamewindow)
{
    while (!gamewindow->should_close())
    {
        int key = GetKeyPressed();
        if (key)
            std::cout << key;
        gamewindow->begin();
        
        crystal::draw_rectangle(RES_X / 2 - 100, RES_Y / 2 - 200, 200, 40, crystal::color::darkgreen);
        crystal::draw_rectangle(RES_X / 2 - 100, RES_Y / 2 - 100, 200, 40, crystal::color::darkgreen);
        gamewindow->end();
    }
}

void    mainloop(crystal::window *gamewindow, board *gameBoard)
{
    mainMenuWindow(gamewindow);
}
