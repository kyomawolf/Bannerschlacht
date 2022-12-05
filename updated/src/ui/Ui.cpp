//
// Created by kyomawolf on 02.10.22.
//

//todo move main menu here

#include "Ui.hpp"

Ui::Ui() : _uiPause(0, 0), _uiIngame(), _uiMain(){}

Ui::Ui(int screen_width, int screen_height) : _uiPause(screen_width, screen_height), _uiIngame(), _uiMain() {
}

void Ui::Draw() {
    if ((_menusEnabled & 1) == 1 )
        _uiPause.Draw();
    if ((_menusEnabled & 2) == 2 )
        _uiMain.Draw();
    if ((_menusEnabled & 4) == 4 )
        _uiIngame.Draw();
}

void Ui::SetPause() { _menusEnabled ^= 1; }

void Ui::SetMainMenu() { _menusEnabled ^= 2; }

void Ui::SetIngame() { _menusEnabled ^= 4; }
