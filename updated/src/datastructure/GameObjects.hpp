#ifndef BANNERSCHLACHT_GAMEOBJECTS_HPP
#define BANNERSCHLACHT_GAMEOBJECTS_HPP
#include "../EventHandlerType.hpp"
#include "../Utils.hpp"
#include "../map/Map.hpp"
#include "BaseData.hpp"

class Map;

class InGame : public EventHandlerType {
private:
protected:
    Map*              _gamemap;
    raylib::Camera2D* _cam;
public:
    bool Handler() override;

    Map *GetGamemap() const;

    void SetGamemap(MapData& gamemap);

    raylib::Camera2D *GetCam() const;

    void SetCam(raylib::Camera2D *cam);
};

class MenuMain : public EventHandlerType {
    private:
    protected:
    std::vector<Button> _buttonList;

    public:
    void AddButton(const Button& newButton);
    bool Handler() override;
    void DrawElements();
};

class UiInGame : public EventHandlerType {
private:
protected:
    std::vector<Button> _buttonList;
public:
    bool Handler() override;
    void AddButton(const Button& newButton);
    void DrawElements();
};
#endif