
#include "raylib-cpp.hpp"

class Button {
private:
    RVector2 _position; ///upper left corner
    RVector2 _clickSize; ///rectangle, if _isCircular == true only x value will be used as radius
    bool     _isCircular;

    raylib::Color    _tintColor = {255, 255, 255, 255};
    raylib::Texture* _buttonTexture = nullptr;
public:
    Button();
    explicit Button(RVector2 initPosition, RVector2 initClickSize = {0, 0});
    Button(RVector2 initPosition, RVector2 initClickSize, bool initCircle = false);
    ~Button();

    void Draw();

    void        SetIsCircular(bool val);
    void        SetPosition(RVector2 val);
    void        SetClickSize(RVector2 val);
    void        SetTexture(raylib::Texture& val);
    void        SetColor(Color val);

    [[nodiscard]] Color        GetColor()     const;
    [[nodiscard]] bool        GetIsCircular() const;
    [[nodiscard]] RVector2    GetPosition()   const;
    [[nodiscard]] RVector2    GetClickSize()  const;
    [[nodiscard]] Texture*    GetTexture()    const;
};