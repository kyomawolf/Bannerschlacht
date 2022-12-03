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
protected:
    raylib::Window& _window;
public:
    const scenes sceneType;
    Scene(scenes newSceneType, raylib::Window& windowReference);
    virtual int Play() = 0;

    virtual ~Scene();
};

class MainMenuScene : public Scene {
private:
    MenuMain& _menu;
public:
    [[nodiscard]] const MenuMain &getMenu() const;

    void setMenu(const MenuMain &menu);

public:
    MainMenuScene(scenes newSceneType, raylib::Window &windowReference, MenuMain &menu);
    int Play() override;
};

class GameScene : public Scene {
private:
    RVector2&             _camPos;
    raylib::Camera2D&     _camera;
    Map&                  _map;
    std::shared_ptr<Data> _data;
    UiInGame&             _gameUi;
public:
    GameScene(scenes newSceneType, raylib::Window &windowReference, RVector2 &camPos,
              raylib::Camera2D &camera, std::shared_ptr<Data> data, Map &map, UiInGame &gameUi);
    int Play() override;
};
#endif //BANNERSCHLACHT_SCENE_HPP

