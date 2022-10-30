#pragma once
#include "EventHandlerType.hpp"
#include "Utils.hpp"
#include <any>

class InGame : public EventHandlerType {
private:
protected:
public:
    bool Handler() override;
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
public:
    bool Handler() override;
};
