#ifndef BANNERSCHLACHT_UTILS_HPP
#define BANNERSCHLACHT_UTILS_HPP
#include "raylib-cpp.hpp"
#include <map>

enum scenes {MAINMENU, GAME, ENUMCOUNT = GAME, LOADMENU};

typedef struct TileIndex {
    TileIndex(long x, long y);
    TileIndex(const TileIndex& other);
    TileIndex(const raylib::Vector2& vec);
    TileIndex& operator=(const TileIndex& other);

    long    x;
    long    y;
    bool    operator<(const TileIndex& other) const;
    bool    operator>(const TileIndex& other) const;
    bool    operator<=(const TileIndex& other) const;
    bool    operator>=(const TileIndex& other) const;
    bool    operator==(const TileIndex& other) const;
    bool    operator!=(const TileIndex& other) const;
}   TileIdx;

std::ostream& operator<<(std::ostream& o, const TileIndex& value);

class Button {
private:
    void         (*_callableFunction)(void) = nullptr;
    RVector2     _position; ///upper left corner
    RVector2     _clickSize; ///rectangle, [_isCircular == true] only x value will be used as radius
    std::string  _text;
    bool         _isCircular;
    raylib::Color    _tintColor = {255, 255, 255, 255};
    raylib::Texture* _buttonTexture = nullptr; //todo shared pointer
public:
    Button();
//    explicit Button(RVector2 initPosition, RVector2 initClickSize = {0, 0});
    Button(RVector2 initPosition, RVector2 initClickSize, bool initCircle = false);
    ~Button();

    void Draw();
    [[nodiscard]] bool IsInside(const RVector2& cpos) const;
    //actionhandlerobject(maybe multiple for different parts of the system (sound, etc)) param1: action_id(as string?), action (as integer: 0 invert (if on turn off, vice versa; 1 on; 2 off)
    void        ButtonAction(std::map<std::string, int>& actionHandlerObject, std::string& actionId, int action = 0);
    void        SetText(const std::string& text);
    void        SetIsCircular(bool val);
    void        SetPosition(RVector2 val);
    void        SetClickSize(RVector2 val);
    void        SetTexture(raylib::Texture& val);
    void        SetColor(Color val);
    void        FunctionCall();
    void        SetCallableFunction(void (*callableFunction)(void));


    [[nodiscard]] Color              GetColor()      const;
    [[nodiscard]] bool               GetIsCircular() const;
    [[nodiscard]] RVector2           GetPosition()   const;
    [[nodiscard]] RVector2           GetClickSize()  const;
    [[nodiscard]] Texture*           GetTexture()    const;
    [[nodiscard]] const std::string& GetText()       const;
};
#endif

