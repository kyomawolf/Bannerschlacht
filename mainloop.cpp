#include <raylib.h>
#include <iostream>
#include "unit.hpp"

int main() {
    unit    soldier = swordsmen();
    int resolution_x    = 800;
    int resolution_y    = 600;


    InitWindow(resolution_x, resolution_y, "Bannerschlacht");
    while (!WindowShouldClose()) {
        //draw_units();
        
        //handle_input();
        //ai_action();
    }
}