//
// Created by Jascha Kasper on 11/6/22.
//

#include "Scene.hpp"
#include "ui/ObjectLayer.hpp"
#include <iostream>

extern enum scenes global_scene_var;
void InputHandler(raylib::Camera2D& cam, raylib::Vector2& cam_pos, raylib::Window& win);

//int Scene::Play() {
//#ifdef DEBUG
//    std::cerr << "default function called" << std::endl;
//#endif
//    return 0;
//}

Scene::Scene(scenes newSceneType, raylib::Window& windowReference) : _window(windowReference), sceneType(newSceneType) { }

Scene::~Scene() { }

MainMenuScene::MainMenuScene(scenes newSceneType, raylib::Window &windowReference, MenuMain &menu) : Scene(newSceneType,
                                                                                                           windowReference),
                                                                                                     _menu(menu) {}

int MainMenuScene::Play() {
    _window.BeginDrawing();

    _window.ClearBackground(raylib::Color::RayWhite());
    _window.DrawFPS();
    _menu.Handler();
    _menu.DrawElements();
    _window.EndDrawing();
}

const MenuMain &MainMenuScene::getMenu() const {
    return _menu;
}

void MainMenuScene::setMenu(const MenuMain &menu) {
    _menu = menu;
}

GameScene::GameScene(scenes newSceneType, raylib::Window &windowReference, RVector2 &camPos,
                     raylib::Camera2D &camera, Data *data, Map &map, UiInGame &gameUi)
        : Scene(newSceneType, windowReference), _camPos(camPos), _camera(camera), _map(map), _data(data),
          _gameUi(gameUi) {}

int GameScene::Play() {
    InGame gameEventHandler;
    gameEventHandler.SetGamemap(&_map);
    gameEventHandler.SetCam(&_camera);
    gameEventHandler.EnableHandler();
    _gameUi.EnableHandler();
    ObjectLayer ui;
    ObjectLayer game(&ui, nullptr);
    ui.SetEventHandler(&_gameUi);
    game.SetEventHandler(&gameEventHandler);
    ui.SetChild(&game);
    while (!WindowShouldClose()) {

        _window.BeginDrawing();

        _camera.BeginMode();
        _window.ClearBackground(raylib::Color::RayWhite());
//        std::cerr << "after" << std::endl;
        _map.Draw();
        //collection.draw(unitData);

        ///inputhandler
//        UiObject.Handler();
        InputHandler(_camera, _camPos, _window);
        if (GetKeyPressed() || raylib::Mouse::IsButtonPressed(0) || raylib::Mouse::IsButtonPressed(1))
            ui.CallEvent();
        if (IsKeyPressed(KEY_SPACE)) {
            for (unsigned int i = 0; i < _map._size.x; i++) {
                for (unsigned int ii = 0; ii != _map._size.y; ii++) {
                    if (_map.at(i, ii).GetInit())
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
        _window.DrawFPS();
//        rec.Draw(raylib::Color::Red());
//        gameData.gameUi.Draw();
        _window.EndDrawing();
    }
    global_scene_var = MAINMENU;
    ///TODO: Setup quads as clickable
}
