#include "map.hpp"
#include "../inc/raylib-cpp.hpp"

//int main_game_loop(data *gameData, uiObj *ui) {
//    process();
//    render();
//}


void move(raylib::Vector2& cam_pos, raylib::Window& win) {
    if (IsKeyDown('W')) {
        cam_pos.y -= 11 * (double) (100.0 / win.GetFPS());
    } if (IsKeyDown('S')) {
        cam_pos.y += 11 * (double) (100.0 / win.GetFPS());
    } if (IsKeyDown('A')) {
        cam_pos.x -= 11 * (double) (100.0 / win.GetFPS());
    } if (IsKeyDown('D')) {
        cam_pos.x += 11 * (double) (100.0 / win.GetFPS());
    }
}


int main () {
    map gamemap(10, 10);

    raylib::Window win(920, 1080, "testmap-0");
    raylib::Vector2 cam_pos(0,0);
    raylib::Camera2D cam(cam_pos, raylib::Vector2(0, 0));
    win.SetTargetFPS(70);
    raylib::Texture quad(raylib::Image(std::string("../rectangle.png")));

    while(!win.ShouldClose()) {
        win.BeginDrawing();
        cam.BeginMode();
        win.ClearBackground(raylib::Color::RayWhite());
        gamemap.draw(quad);
        move(cam_pos, win);
        cam.SetTarget(cam_pos);
        cam.EndMode();
        win.EndDrawing();
        ///TODO: Setup quads as clickable
    }

    return 0;
//    data* gameData = new data(/*config file?*/);
//    return main_game_loop(gameData, uiStartup());
}