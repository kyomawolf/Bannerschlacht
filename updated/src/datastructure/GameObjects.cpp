#include "GameObjects.hpp"
#include "raylib-cpp.hpp"
#include <iostream>
extern enum scenes global_scene_var;

//todo move gameobjects to a different structure => gameobjects/<objectname> also current classes should be scenes probably

bool InGame::Handler() {
    bool returnValue = false;
#ifdef DEBUG
//    std::cerr << "InGame class Handler() called" << std::endl;
#endif //DEBUG
    if (raylib::Mouse::IsButtonPressed(0) || raylib::Mouse::IsButtonPressed(1)) {
        TileIndex vec(_cam->GetScreenToWorld(raylib::Mouse::GetPosition()));
        _gamemap->OnClick(vec);
        std::cout << _gamemap->positionToIndex(vec) << std::endl;
        returnValue = true;
    }
    /// game movement
    if (raylib::Mouse::GetWheelMove() > 0 && (_cam->zoom + 0.06) < 1.5) {
        _cam->zoom += 0.06;
        std::cout << "zoom: " << _cam->zoom << std::endl;
    }
    if (raylib::Mouse::GetWheelMove() < 0 && (_cam->zoom - 0.06) > 0.1) {
        _cam->zoom += -0.06;
        std::cout << "zoom: " << _cam->zoom << std::endl;
    }
    if (IsKeyDown(KEY_W)) {
        _camPos.y += -18;
        returnValue = true;
    } if (IsKeyDown(KEY_S)) {
        _camPos.y += 18;
        returnValue = true;
    } if (IsKeyDown(KEY_A)) {
        _camPos.x += -18;
        returnValue = true;
    } if (IsKeyDown(KEY_D)) {
        _camPos.x += 18;
        returnValue = true;
    }
    return returnValue;
}

Map *InGame::GetGamemap() const {
    return _gamemap;
}

void InGame::SetGamemap(MapData& gamemap) {
    _gamemap = gamemap.GetMapPointer();
}

raylib::Camera2D *InGame::GetCam() const {
    return _cam;
}

void InGame::SetCam(raylib::Camera2D *cam) {
    _cam = cam;
}

InGame::InGame(raylib::Vector2 &camPos) : _camPos(camPos) {}


bool MenuMain::Handler() {
#ifdef DEBUG
//    std::cerr << "MainMenu class Handler() called" << std::endl;
#endif //DEBUG
    RVector2  currMousePos = raylib::Mouse::GetPosition();//TODO init
    ///check buttonList for clickable area
    for (auto & i : _buttonList) {
        if (i.IsInside(currMousePos)) {
            if (raylib::Mouse::IsButtonReleased(0)) {
                if (i.GetText() == "Exit")
                    exit(0); // TODO set as a scene variable
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
    for (auto i = _buttonList.rbegin(); i != _buttonList.rend(); i++)
        i->Draw();
}

bool UiInGame::Handler() {
    RVector2  currMousePos = raylib::Mouse::GetPosition();
    ///check buttonList for clickable area
    for (auto & i : _buttonList) {
        if (i.IsInside(currMousePos)) {
            if (IsMouseButtonPressed(0)) {
                std::cout << i.GetClickSize() << std::endl;
                std::cout << "clicked " << i.GetText() << std::endl;
                i.FunctionCall();
                return true;
            }
            break;
        }
        //do something
    }
    //call ingame handler
    return false;
}
