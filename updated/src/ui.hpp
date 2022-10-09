//
// Created by kyomawolf on 02.10.22.
//
#include "raylib-cpp.hpp"


class Ui {
private:
    /// bits: 1 pause | 2 main_menu | 4 ingame
    ///yes i know i should just use 3 booleans, but i wanted to try it out
    int menus_enabled = 1;
public:
    class PauseMenu {
    private:
//        measures:
//        height from above should be 1/6 (from below as well)
//        should be centered in the middle. there maybe 1/6 of the screen width
        raylib::Rectangle   pause_frame; //replace later with a texture
    public:
        PauseMenu(int screen_width, int screen_height) : pause_frame(screen_width * 0.5 - screen_width * 0.08, screen_height * 0.16,
                                                                     screen_width * 0.16, screen_height * 0.66) { }
        void draw() {
            pause_frame.Draw(raylib::Color::Beige());
        }
    };

    class Ingame {
    public:
        void draw() {}
    };

    class MainMenu {
    public:
        void draw() {}
    };

    Ui(int screen_width, int screen_height) : ui_pause(screen_width, screen_height), ui_ingame(), ui_main() {
    }
    void draw() {
        if ((menus_enabled & 1) == 1 )
            ui_pause.draw();
        if ((menus_enabled & 2) == 2 )
            ui_main.draw();
        if ((menus_enabled & 4) == 4 )
            ui_ingame.draw();
    }
    void    SetPause() { menus_enabled ^= 1; };
    void    SetMainMenu() { menus_enabled ^= 2; };
    void    SetIngame() { menus_enabled ^= 4; };

private:
    PauseMenu   ui_pause;
    Ingame      ui_ingame;
    MainMenu    ui_main;


};