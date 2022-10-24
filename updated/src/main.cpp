#include <iostream>
#include "Map.hpp"
#include "Ui.hpp"
#include "Parser.hpp"
#include "../inc/raylib-cpp.hpp"

//int main_game_loop(Data *gameData, uiObj *ui) {
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

void    Setup() { }

void    MainGameLoop(raylib::Window& win, raylib::Camera2D& cam, RVector2& cameraPos, Map& gamemap, Data& gameData) {
    raylib::Color textColor(BLUE);
    raylib::Texture quad(raylib::Image(std::string("../rectangle.png")));
    raylib::Rectangle rec(10, 10, 700, 20);
    //Ui game_ui(win.GetWidth(), win.GetHeight());
    while(!win.ShouldClose()) {
        win.BeginDrawing();

        ///ingame
        cam.BeginMode();
        win.ClearBackground(raylib::Color::RayWhite());
//        std::cerr << "after" << std::endl;
        gamemap.Draw(quad);
        //collection.draw(unitData);
        move(cam, cameraPos, win);
        if (IsKeyPressed(KEY_SPACE)) {
            for (unsigned int i = 0; i < gamemap._size.x; i++) {
                for (unsigned int ii = 0; ii != gamemap._size.y; ii++) {
                    if (gamemap.at(i, ii).GetInit())
                        std::cout << i << " " << ii << "initialized" << std::endl;
                }
            }
        }
        if (raylib::Mouse::IsButtonReleased(0)) {
            //todo check if ui has been clicked
            raylib::Vector2 vec = cam.GetScreenToWorld(raylib::Mouse::GetPosition());
            gamemap.OnClick(vec);
            vec = gamemap.positionToIndex(vec);
            std::cout << vec << std::endl;
        }
        cam.SetTarget(cameraPos);
        cam.EndMode();

        ///overlay
        win.DrawFPS();
//        rec.Draw(raylib::Color::Red());
        //game_ui.draw();
        win.EndDrawing();
        ///TODO: Setup quads as clickable
    }
}

int main () {
    Parser  par;
    Data*   data = new Data();
    try {
        par.Map("src/test.map", *data);
    } catch (Parser::ParserException &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "parsed map" << std::endl;
    Map gamemap(par.getMapData().width, par.getMapData().height);
    std::cout << "loaded map" << std::endl;

    raylib::Window win(1080, 720, "Schlacht ver. 0.0.2");
    raylib::Vector2 cam_pos(win.GetWidth() / 2, win.GetHeight() / 2);
    raylib::Camera2D cam(cam_pos, raylib::Vector2(0, 0));
    win.SetTargetFPS(140);
    raylib::Texture unit_text(raylib::Image(std::string("../red_dot.png")));

    const std::vector<Data::UnitData> tmp = par.getUnitData();
    for (auto i = tmp.begin(); i < tmp.end(); i++) {
        try {
            gamemap.at(i->x, i->y).SetEntry(i->class_d);
            gamemap.at(i->x, i->y).GetEntry()->tex = &unit_text;
            gamemap.at(i->x, i->y).SetInit(true);
        } catch (...) {
            std::cout << "out of range" << std::endl;
        }
    }
    MainGameLoop(win, cam, cam_pos, gamemap, data);
    return 0;
//    Data* gameData = new Data(/*config file?*/);
//    return main_game_loop(gameData, uiStartup());
}
