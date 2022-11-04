#include "GameObjects.hpp"
#include "raylib-cpp.hpp"
#include <iostream>
enum scenes {MAINMENU, LOADMENU, GAME};
extern enum scenes global_scene_var;

bool InGame::Handler() {
#ifdef DEBUG
    std::cerr << "InGame class Handler() called" << std::endl;
#endif //DEBUG
    if (raylib::Mouse::IsButtonPressed(0)) {
        raylib::Vector2 vec = _cam->GetScreenToWorld(raylib::Mouse::GetPosition());
        _gamemap->OnClick(vec);
        std::cout << _gamemap->positionToIndex(vec) << std::endl;
        return true;
    }
    return false;
}

Map *InGame::GetGamemap() const {
    return _gamemap;
}

void InGame::SetGamemap(Map *gamemap) {
    _gamemap = gamemap;
}

raylib::Camera2D *InGame::GetCam() const {
    return _cam;
}

void InGame::SetCam(raylib::Camera2D *cam) {
    _cam = cam;
}

bool MenuMain::Handler() {
#ifdef DEBUG
//    std::cerr << "MainMenu class Handler() called" << std::endl;
#endif //DEBUG
    RVector2  currMousePos = raylib::Mouse::GetPosition();//TODO init
    ///check buttonList for clickable area
    for (auto & i : _buttonList) {
        if (i.IsInside(currMousePos)) {
            if (raylib::Mouse::IsButtonReleased(0)) {
                std::cout << "clicked " << i.GetText() << std::endl;
                global_scene_var = GAME;
                return true;
            }
            break;
        }
            //do something
    }
    return false;
}

void MenuMain::AddButton(const Button& newButton) {
    _buttonList.push_back(newButton);
}

void MenuMain::DrawElements() {
    for (auto & i : _buttonList)
        i.Draw();
}

void UiInGame::AddButton(const Button& newButton) {
    _buttonList.push_back(newButton);
}

void UiInGame::DrawElements() {
    for (auto & i : _buttonList)
        i.Draw();
}

bool UiInGame::Handler() {
#ifdef DEBUG
//    std::cerr << "Ui - InGame class Handler() called" << std::endl;
#endif //DEBUG
    RVector2  currMousePos = raylib::Mouse::GetPosition();
    ///check buttonList for clickable area
    for (auto & i : _buttonList) {
        if (i.IsInside(currMousePos)) {
            if (IsMouseButtonPressed(0)) {
                std::cout << "clicked " << i.GetText() << std::endl;
                return true;
            }
            break;
        }
        //do something
    }
    //call ingame handler
    return false;
}
