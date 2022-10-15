#include <iostream>
#include "map.hpp"
#include "ui.hpp"
#include "../inc/raylib-cpp.hpp"

//int main_game_loop(data *gameData, uiObj *ui) {
//    process();
//    render();
//}

#ifndef VEC2OVERLOAD
#define VEC2OVERLOAD
std::ostream& operator<<(std::ostream& o, const raylib::Vector2& vec) {
    o << vec.x << " " << vec.y;
    return o;
}
#endif /*VEC2OVERLOAD*/


void move(raylib::Camera2D& cam, raylib::Vector2& cam_pos, raylib::Window& win) {
    static int stage = 0;
    if (IsKeyDown('W')) {
        cam_pos.y -= 11 * (float) (100.0 / win.GetFPS());
    } if (IsKeyDown('S')) {
        cam_pos.y += 11 * (float) (100.0 / win.GetFPS());
    } if (IsKeyDown('A')) {
        cam_pos.x -= 11 * (float) (100.0 / win.GetFPS());
    } if (IsKeyDown('D')) {
        cam_pos.x += 11 * (float) (100.0 / win.GetFPS());
    }
    raylib::Vector2 vec = raylib::Mouse::GetPosition();
    vec.x = vec.x - win.GetWidth() / 2;
    vec.y = vec.y - win.GetHeight() / 2;
    if (raylib::Mouse::GetWheelMove() < 0 && stage < 9) {
        ++stage;
        cam.SetZoom(cam.GetZoom() - 0.1);
//        std::cout << raylib::Vector2(cam.GetTarget().x - vec.x, cam.GetTarget().y - vec.y) << std::endl;
        cam.SetTarget(raylib::Vector2(cam.GetTarget().x - vec.x, cam.GetTarget().y - vec.y));
    }
    else if (raylib::Mouse::GetWheelMove() > 0 && stage > -10) {
        --stage;
        cam.SetZoom(cam.GetZoom() + 0.1);
//        std::cout << raylib::Vector2(cam.GetTarget().x - vec.x, cam.GetTarget().y - vec.y) << std::endl;
        cam.SetTarget(raylib::Vector2(cam.GetTarget().x - vec.x, cam.GetTarget().y - vec.y));
    }

}


int main () {
    map gamemap(10, 10);

    raylib::Window win(1080, 720, "testmap-0");
    raylib::Vector2 cam_pos(win.GetWidth() / 2,win.GetHeight() / 2);
    raylib::Camera2D cam(cam_pos, raylib::Vector2(0, 0));
    win.SetTargetFPS(140);
    raylib::Color textColor(BLUE);
    raylib::Texture quad(raylib::Image(std::string("../rectangle.png")));
    raylib::Texture unit_text(raylib::Image(std::string("../red_dot.png")));
    raylib::Rectangle rec(10, 10, 700, 20);
    //Ui game_ui(win.GetWidth(), win.GetHeight());
    Unit* std_unit = new Unit(unit_text);
    gamemap.at(2, 2).SetEntry(std_unit);
    while(!win.ShouldClose()) {
        win.BeginDrawing();

        ///ingame
        cam.BeginMode();
        win.ClearBackground(raylib::Color::RayWhite());
//        std::cerr << "after" << std::endl;
        gamemap.draw(quad);
        //collection.draw(units);
        move(cam, cam_pos, win);
        if (raylib::Mouse::IsButtonReleased(0)) {
            //todo check if ui has been clicked
            raylib::Vector2 vec = cam.GetScreenToWorld(raylib::Mouse::GetPosition());
            gamemap.OnClick(vec);
            vec = gamemap.positionToIndex(vec);
            std::cout << vec << std::endl;
        }
        cam.SetTarget(cam_pos);
        cam.EndMode();

        ///overlay
        win.DrawFPS();
//        rec.Draw(raylib::Color::Red());
        //game_ui.draw();
        win.EndDrawing();
        ///TODO: Setup quads as clickable
    }
    delete std_unit;
    return 0;
//    data* gameData = new data(/*config file?*/);
//    return main_game_loop(gameData, uiStartup());
}
