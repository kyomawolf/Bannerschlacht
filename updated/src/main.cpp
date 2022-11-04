#include <iostream>
#include "Map.hpp"
#include "Ui.hpp"
#include "Parser.hpp"
#include "../inc/raylib-cpp.hpp"
#include "ObjectLayer.hpp"
#include "GameObjects.hpp"

//int main_game_loop(Data *gameData, uiObj *ui) {
//    process();
//    render();
//}


enum scenes {MAINMENU, LOADMENU, GAME};

enum scenes global_scene_var;

void InputHandler(raylib::Camera2D& cam, raylib::Vector2& cam_pos, raylib::Window& win) {
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
//    if (IsKeyPressed(KEY_SPACE)) {
//        gameData.gameUi.SetPause();
//        gameData.gameUi.SetIngame();
//    }

}

void    Setup() { }

void    MainGameLoop(raylib::Window& win, raylib::Camera2D& cam, RVector2& cameraPos, Map& gamemap, Data& gameData, UiInGame& UiObject) {
    //Ui game_ui(win.GetWidth(), win.GetHeight());
    ///ingame
    InGame gameEventHandler;
    gameEventHandler.SetGamemap(&gamemap);
    gameEventHandler.SetCam(&cam);
    gameEventHandler.EnableHandler();
    UiObject.EnableHandler();
    ObjectLayer ui;
    ObjectLayer game(&ui, nullptr);
    ui.SetEventHandler(&UiObject);
    game.SetEventHandler(&gameEventHandler);
    ui.SetChild(&game);
    while (!WindowShouldClose()) {

        win.BeginDrawing();

        cam.BeginMode();
        win.ClearBackground(raylib::Color::RayWhite());
//        std::cerr << "after" << std::endl;
        gamemap.Draw();
        //collection.draw(unitData);

        ///inputhandler
//        UiObject.Handler();
        InputHandler(cam, cameraPos, win);
        if (GetKeyPressed() || raylib::Mouse::IsButtonPressed(0) || raylib::Mouse::IsButtonPressed(1))
            ui.CallEvent();
        if (IsKeyPressed(KEY_SPACE)) {
            for (unsigned int i = 0; i < gamemap._size.x; i++) {
                for (unsigned int ii = 0; ii != gamemap._size.y; ii++) {
                    if (gamemap.at(i, ii).GetInit())
                        std::cout << i << " " << ii << "initialized" << std::endl;
                }
            }
        }

//        if (IsMouseButtonPressed(0)) {
//            raylib::Vector2 vec = cam.GetScreenToWorld(raylib::Mouse::GetPosition());
//            gamemap.OnClick(vec);
//            vec = gamemap.positionToIndex(vec);
//            std::cout << vec << std::endl;
//        }
        cam.SetTarget(cameraPos);
        cam.EndMode();
        ///overlay
        UiObject.DrawElements();
        win.DrawFPS();
//        rec.Draw(raylib::Color::Red());
//        gameData.gameUi.Draw();
        win.EndDrawing();
    }
    global_scene_var = MAINMENU;
        ///TODO: Setup quads as clickable
}


void MainMenuLoop(raylib::Window& win, MenuMain& mainGameMenu, Data& gameData) {
        win.BeginDrawing();

        win.ClearBackground(raylib::Color::RayWhite());
        win.DrawFPS();
        mainGameMenu.Handler();
        mainGameMenu.DrawElements();
        win.EndDrawing();
};

void    SetUpButtonsMainMenu(MenuMain& menuObject, raylib::Window& win) {
    Button      buttonNewGame( {static_cast<float>(win.GetWidth()) / 2 - 60, static_cast<float>(win.GetHeight()) / 2 - 30} , {120, 20});
    buttonNewGame.SetColor(raylib::GREEN);
    buttonNewGame.SetText("New Game");

    Button      buttonLoadGame({static_cast<float>(win.GetWidth()) / 2 - 60, static_cast<float>(win.GetHeight()) / 2 + 10} , {120, 20});
    buttonLoadGame.SetColor(raylib::ORANGE);
    buttonLoadGame.SetText("Load Game");

    Button      buttonExitGame({static_cast<float>(win.GetWidth()) / 2 - 60, static_cast<float>(win.GetHeight()) / 2 + 50} , {120, 20});
    buttonExitGame.SetColor(raylib::RED);
    buttonExitGame.SetText("Exit");
    menuObject.AddButton(buttonNewGame);
    menuObject.AddButton(buttonLoadGame);
    menuObject.AddButton(buttonExitGame);
}

void    SetUpButtonsMainUi(UiInGame& UiObject, raylib::Window& win) {
    Button      buttonVoid({static_cast<float>(win.GetWidth()) * 0.2f, static_cast<float>(win.GetHeight()) * 0.8f}, {static_cast<float>(win.GetWidth()) * 0.6f, static_cast<float>(win.GetHeight()) * 0.2f});
    buttonVoid.SetColor(raylib::BEIGE);
    UiObject.AddButton(buttonVoid);
}

int main () {
    Parser  par;
    Data*   data = new Data();

    global_scene_var = MAINMENU;

    try {
        par.Map("src/test.map", *data);
    } catch (Parser::ParserException &e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "parsed map" << std::endl;
    MapData *mapData = dynamic_cast<MapData *>(data->FindNextIdent(Data::MAP));
    Map gamemap(mapData->GetWidth(), mapData->GetHeight());
    std::cout << "loaded map" << std::endl;

    raylib::Window win(1080, 720, "Schlacht ver. 0.0.4");
    data->gameUi = Ui(win.GetWidth(), win.GetHeight());
    raylib::Vector2 cam_pos(win.GetWidth() / 2, win.GetHeight() / 2);
    raylib::Camera2D cam(cam_pos, raylib::Vector2(0, 0));
    win.SetTargetFPS(140);

    MenuMain    mainGameMenu;
    UiInGame    mainUi;
    ///Main Menu Buttons:

    SetUpButtonsMainMenu(mainGameMenu, win);
    SetUpButtonsMainUi(mainUi, win);

    raylib::Texture unit_text(raylib::Image(std::string("../red_dot.png")));

    for (auto i = data->vecUnits.begin(); i < data->vecUnits.end(); i++) {
        try {
            gamemap.at((*i)->GetX(), (*i)->GetY()).SetEntry(*i);
            gamemap.at((*i)->GetX(), (*i)->GetY()).GetEntry()->tex = &unit_text;
            gamemap.at((*i)->GetX(), (*i)->GetY()).SetInit(true);
        } catch (...) {
            std::cout << "out of range" << std::endl;
        }
    }
    raylib::Texture quad(raylib::Image(std::string("../rectangle.png")));
//    raylib::Rectangle rec(10, 10, 700, 20);
    gamemap.SetTileTex(&quad);
    while(!win.ShouldClose()) {
        switch (global_scene_var) {
            case MAINMENU:
                MainMenuLoop(win, mainGameMenu,*data);
                break;
            case LOADMENU:
                break;
            case GAME:
                MainGameLoop(win, cam, cam_pos, gamemap, *data, mainUi);
                break;
        }
//        win.BeginDrawing();
//
//        win.ClearBackground(raylib::Color::RayWhite());
//        win.DrawFPS();
//        mainGameMenu.Handler();
//        mainGameMenu.DrawElements();
//        win.EndDrawing();
//        ///TODO check static variables to change scenes
        //switch(scene) {
        //  case MAINMENU:
        //  case LOADMENU:
        //  case LOADINGSCREEN:
        //  case GAME:
        //}
    }
    return 0;
    Data* gameData = new Data(/*config file?*/);
//    return main_game_loop(gameData, uiStartup());
}
