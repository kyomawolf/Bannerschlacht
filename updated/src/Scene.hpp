//
// Created by Jascha Kasper on 11/6/22.
//
#ifndef BANNERSCHLACHT_SCENE_HPP
#define BANNERSCHLACHT_SCENE_HPP
#include "Utils.hpp"
#include "datastructure/GameObjects.hpp"
#include "raylib-cpp.hpp"
class Data;

class Scene {
private:
    scenes sceneType;
public:
    Scene(scenes newSceneType);
    virtual int Play() = 0;

    scenes GetSceneType() const;

    virtual ~Scene();
};

class MainMenuScene : public Scene {
private:
    MenuMain& _menu;
public:
    [[nodiscard]] const MenuMain &getMenu() const;

    void setMenu(const MenuMain &menu);

public:
    MainMenuScene(scenes newSceneType, MenuMain &menu);
    int Play() override;
};

class GameScene : public Scene {
private:
    RVector2&             _camPos;
    raylib::Camera2D&     _camera;
    UiInGame&             _gameUi;
    int                   _mapID;
public:
    GameScene(scenes newSceneType, RVector2 &camPos,
              raylib::Camera2D &camera, UiInGame &gameUi, int newMapID);
    int Play() override;
};
#endif //BANNERSCHLACHT_SCENE_HPP

