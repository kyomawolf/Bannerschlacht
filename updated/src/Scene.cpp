//
// Created by Jascha Kasper on 11/6/22.
//

#include "ui/ObjectLayer.hpp"
#include "datastructure/Data.hpp"
#include <iostream>
#include <utility>

extern enum scenes global_scene_var;
void InputHandler(raylib::Camera2D& cam, raylib::Vector2& cam_pos, raylib::Window& win);

//int Scene::Play() {
//#ifdef DEBUG
//    std::cerr << "default function called" << std::endl;
//#endif
//    return 0;
//}

Scene::Scene(scenes newSceneType) : sceneType(newSceneType) { }

Scene::~Scene() { }

scenes Scene::GetSceneType() const {
    return sceneType;
}

MainMenuScene::MainMenuScene(scenes newSceneType, MenuMain &menu) : Scene(newSceneType),
                                                                                                     _menu(menu) {}

int MainMenuScene::Play() {
    std::unique_ptr<raylib::Window>& _window = Data::GetInstance().GetWindow();

    _window->ClearBackground(raylib::Color::RayWhite());
    _window->DrawFPS();
    _menu.Handler();
    _menu.DrawElements();
    _window->EndDrawing();
    return 0;
}

const MenuMain &MainMenuScene::getMenu() const {
    return _menu;
}

void MainMenuScene::setMenu(const MenuMain &menu) {
    _menu = menu;
}

GameScene::GameScene(scenes newSceneType, RVector2 &camPos,
                     raylib::Camera2D &camera, UiInGame &gameUi, int newMapID)
        : Scene(newSceneType), _camPos(camPos), _camera(camera),
          _gameUi(gameUi), _mapID(newMapID) {}

int GameScene::Play() {
    std::unique_ptr<raylib::Window>& _window = Data::GetInstance().GetWindow();
    InGame gameEventHandler(_camPos);
    gameEventHandler.SetGamemap(Data::GetInstance().GetMapDataByIdx(_mapID));
    gameEventHandler.SetCam(&_camera);
    gameEventHandler.EnableHandler();
    _gameUi.EnableHandler();
    ObjectLayer ui;
    ObjectLayer game(&ui, nullptr);
    ui.SetEventHandler(&_gameUi);
    game.SetEventHandler(&gameEventHandler);
    ui.SetChild(&game);
    while (!WindowShouldClose()) {

        _window->BeginDrawing();

        _camera.BeginMode();
        _window->ClearBackground(raylib::Color::RayWhite());
//        std::cerr << "after" << std::endl;
        /// currently hardcoded, but should be set with a 'current game' variable
        Data::GetInstance().GetMapDataByIdx(_mapID).GetMapPointer()->Draw();
        //collection.draw(unitData);

        ///inputhandler
//        UiObject.Handler();
        //InputHandler(_camera, _camPos, _window);
//        if (/*any key pressed ||*/ raylib::Mouse::IsButtonPressed(0) || raylib::Mouse::IsButtonPressed(1)) {
            ui.CallEvent();
//            std::cout << _camPos.x << " " << _camPos.y << std::endl;
//        }
        if (IsKeyPressed(KEY_SPACE)) {
            for (unsigned int i = 0; i < Data::GetInstance().GetMapDataByIdx(0).GetWidth(); i++) {
                for (unsigned int ii = 0; ii != Data::GetInstance().GetMapDataByIdx(0).GetHeight(); ii++) {
                    if (Data::GetInstance().GetMapDataByIdx(0).GetMapPointer()->at(i, ii).GetInit())
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
        _camera.SetTarget(_camPos);
        _camera.EndMode();
        ///overlay
        _gameUi.DrawElements();
        _window->DrawFPS();
//        rec.Draw(raylib::Color::Red());
//        gameData.gameUi.Draw();
        _window->EndDrawing();
    }
    global_scene_var = MAINMENU;
    ///TODO: Setup quads as clickable
    return 0;
}
