#include "Utils.hpp"

extern raylib::Font wrttxt;

#ifndef VEC2OVERLOAD
#define VEC2OVERLOAD
std::ostream& operator<<(std::ostream& o, const raylib::Vector2& vec) {
    o << vec.x << " " << vec.y;
    return o;
}
#endif /*VEC2OVERLOAD*/

Button::Button() : _position(0, 0), _clickSize(0, 0), _isCircular(false) { }

//Button::Button(RVector2 initPosition, RVector2 initClickSize) : _position(initPosition), _clickSize(initClickSize), _isCircular(false) { }
Button::Button(RVector2 initPosition, RVector2 initClickSize, bool initCircle) : _position(initPosition), _clickSize(initClickSize), _isCircular(initCircle) { }

Button::~Button() { }

void Button::Draw() {
    if (_buttonTexture == nullptr) {
        raylib::Rectangle rec(_position, _clickSize);
        rec.Draw(_tintColor);
        raylib::Text::Draw(_text, _position.x, _position.y, 20, raylib::BLACK);
        return;
    }
    _buttonTexture->Draw(_position, _tintColor);
}

///SETTER

void Button::SetIsCircular(bool val) {
    _isCircular = val;
}

void Button::SetPosition(RVector2 val) {
    _position = val;
}

void Button::SetClickSize(RVector2 val) {
    _clickSize = val;
}

void Button::SetTexture(raylib::Texture &val) {
    _buttonTexture = &val;
}

void Button::SetColor(Color val) {
    _tintColor = val;
}

///GETTER

bool Button::GetIsCircular() const {
    return _isCircular;
}

RVector2 Button::GetPosition() const {
    return _position;
}

RVector2 Button::GetClickSize() const {
    return _clickSize;
}

Texture *Button::GetTexture() const {
    return _buttonTexture;
}

Color Button::GetColor() const {
    return _tintColor;
}

bool Button::IsInside(const RVector2& cpos) const {
    if (_isCircular) {
        if (cpos.x < _position.x || cpos.y < _position.x)
            return false;
        if (cpos.x > _position.x + _clickSize.x || cpos.y > _position.y + _clickSize.y)
            return false;
        return true;
    } else {
        if (cpos.x < _position.x - _clickSize.x || cpos.x > _position.x + _clickSize.x
            || cpos.y < _position.y - _clickSize.y || cpos.y > _position.y + _clickSize.y )
            return false;
        return true;
    }
}

const std::string &Button::GetText() const {
    return _text;
}

void Button::SetText(const std::string &text) {
    _text = text;
}



