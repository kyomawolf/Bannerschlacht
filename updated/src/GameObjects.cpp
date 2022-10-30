#include "GameObjects.hpp"
#include "raylib-cpp.hpp"
#include <iostream>
enum scenes {MAINMENU, LOADMENU, GAME};
extern enum scenes global_scene_var;

bool InGame::Handler() {
#ifdef DEBUG
    std::cerr << "InGame class Handler() called" << std::endl;
#endif //DEBUG
    return false;
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

bool UiInGame::Handler() {
#ifdef DEBUG
    std::cerr << "Ui - InGame class Handler() called" << std::endl;
#endif //DEBUG
    return false;
}
