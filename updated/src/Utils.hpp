#ifndef BANNERSCHLACHT_UTILS_HPP
#define BANNERSCHLACHT_UTILS_HPP
#include "raylib-cpp.hpp"

enum scenes {MAINMENU, GAME, ENUMCOUNT = GAME, LOADMENU};

class Button {
private:
    RVector2     _position; ///upper left corner
    RVector2     _clickSize; ///rectangle, [_isCircular == true] only x value will be used as radius
    std::string  _text;
    bool         _isCircular;
    raylib::Color    _tintColor = {255, 255, 255, 255};
    raylib::Texture* _buttonTexture = nullptr;
public:
    Button();
//    explicit Button(RVector2 initPosition, RVector2 initClickSize = {0, 0});
    Button(RVector2 initPosition, RVector2 initClickSize, bool initCircle = false);
    ~Button();

    void Draw();
    [[nodiscard]] bool IsInside(const RVector2& cpos) const;


    void        SetText(const std::string& text);
    void        SetIsCircular(bool val);
    void        SetPosition(RVector2 val);
    void        SetClickSize(RVector2 val);
    void        SetTexture(raylib::Texture& val);
    void        SetColor(Color val);

    [[nodiscard]] Color              GetColor()      const;
    [[nodiscard]] bool               GetIsCircular() const;
    [[nodiscard]] RVector2           GetPosition()   const;
    [[nodiscard]] RVector2           GetClickSize()  const;
    [[nodiscard]] Texture*           GetTexture()    const;
    [[nodiscard]] const std::string& GetText()       const;
};
#endif

