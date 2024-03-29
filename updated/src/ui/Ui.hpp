//
// Created by kyomawolf on 02.10.22.
//
#ifndef UI_HPP
#define UI_HPP
#include "raylib-cpp.hpp"


class Ui {
private:
    /// bits: 1 pause | 2 main_menu | 4 ingame
    ///yes i know i should just use 3 booleans, but i wanted to try it out
    int _menusEnabled = 1;
public:
    class PauseMenu {
    private:
//        measures:
//        height from above should be 1/6 (from below as well)
//        should be centered in the middle. there maybe 1/6 of the screen width
        raylib::Rectangle   _pauseFrame; //replace later with a texture
    public:
        PauseMenu(int screen_width, int screen_height) : _pauseFrame(screen_width * 0.5 - screen_width * 0.08, screen_height * 0.16,
                                                                     screen_width * 0.16, screen_height * 0.66) { }
        void Draw() {
            _pauseFrame.Draw(raylib::Color::Beige());
        }
    };

    class Ingame {
    public:
        void Draw() {}
    };

    class MainMenu {
    public:
        void Draw() {}
    };

    Ui();
    Ui(int screen_width, int screen_height);
    void Draw();

    void    SetPause();
    void    SetMainMenu();
    void    SetIngame();

private:
    PauseMenu   _uiPause;
    Ingame      _uiIngame;
    MainMenu    _uiMain;


};

#endif /*UI_HPP*/