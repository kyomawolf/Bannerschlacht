#include "Utils.hpp"

Button::Button() : _position(0, 0), _clickSize(0, 0), _isCircular(false) { }

Button::Button(RVector2 initPosition, RVector2 initClickSize) : _position(initPosition), _clickSize(initClickSize), _isCircular(false) { }

Button::Button(RVector2 initPosition, RVector2 initClickSize, bool initCircle)  : _position(initPosition), _clickSize(initClickSize), _isCircular(initCircle) { }

Button::~Button() { }

void Button::Draw() {
    if (_buttonTexture == nullptr) {

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


