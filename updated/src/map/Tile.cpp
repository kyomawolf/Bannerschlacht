//
// Created by kyomawolf on 26.08.22.
//

#include <iostream>
#include "Tile.hpp"
#include "Map.hpp"
#include "../units/Unit.hpp"


void Tile::Draw(unsigned int x, unsigned int y) {
//    std::cout << "test" << std::endl;
    if (_initialized) {
        RVector2 pos = Map::LocalToWorld(x, y);
        pos.x += _paddingLeft;
        pos.y += _paddingTop;
//        std::cout << "in here "<< Map::LocalToWorld(x, y) << std::endl;
        _entry->tex->Draw(pos/* plus padding */, 0, _entry->scale, _entry->player_tints[_entry->GetPlayer()]);
    }
//    std::cout << "after if" << std::endl;
}

bool Tile::MoveUnit(Tile &dest) {
    if (dest.GetEntry() != nullptr || _entry == nullptr)
        return false;
    dest.SetEntry(_entry);
    _entry = nullptr;
    _initialized = false;
    dest.SetInit(true);
    std::cout << "success" << std::endl;
    return true;
}

bool Tile::GetInit() const {
    return _initialized;
}

int Tile::GetCost() const {
    return _cost;
}

void Tile::SetCost(int cost) {
    _cost = cost;
}

Tile::Tile(int x, int y, Map& parent) : _parent(parent), _pos(x, y) { }

Tile::Tile(const Tile& tile) : _cost(tile._cost), _defenceModifier(tile._defenceModifier), _attackModifier(tile._attackModifier), _faceAccess(), _initialized(tile._initialized), _entry(tile._entry), _paddingLeft(tile._paddingLeft), _paddingTop(tile._paddingTop), _parent(tile._parent), _pos(tile._pos) {
    _faceAccess[0] = tile._faceAccess[0];
    _faceAccess[1] = tile._faceAccess[1];
    _faceAccess[2] = tile._faceAccess[2];
    _faceAccess[3] = tile._faceAccess[3];
}

Tile &Tile::operator=(const Tile &other) noexcept {
    _cost = other._cost;
    _defenceModifier = other._defenceModifier;
    _faceAccess[0] = other._faceAccess[0];
    _faceAccess[1] = other._faceAccess[1];
    _faceAccess[2] = other._faceAccess[2];
    _faceAccess[3] = other._faceAccess[3];
    _initialized = other._initialized;
    _entry = other._entry;
    _paddingLeft = other._paddingLeft;
    _paddingTop = other._paddingTop;
    _parent = other._parent;
    _pos = other._pos;//TODO make to map.end()?
    return *this;
}

TileIterator::TileIterator(int x, int y, Map& ref) : _x(x), _y(y), _ref(ref) {}

void TileIterator::operator++() {
    if (_x + 1 < _ref._size.x)
        ++_x;
    else if (_y + 1 < _ref._size.y) {
        _x = 0;
        ++_y;
    }
    else {
        _x = -1;
        _y = -1;
    }
}

const TileIterator TileIterator::operator++(int) {
    TileIterator tmp(*this);
    if (_x + 1 < _ref._size.x)
        ++_x;
    else if (_y + 1 < _ref._size.y) {
        _x = 0;
        ++_y;
    }
    else {
        _x = -1;
        _y = -1;
    }
    return tmp;
}

void TileIterator::operator--() {
    if (_x - 1 > 0)
        --_x;
    else if (_y - 1 > 0) {
        _x = 0;
        --_y;
    }
    else {
        _x = -1;
        _y = -1;
    }
}

const TileIterator TileIterator::operator--(int) {
    TileIterator tmp(*this);
    if (_x - 1 < 0)
        --_x;
    else if (_y - 1 < 0) {
        _x = 0;
        --_y;
    }
    else {
        _x = -1;
        _y = -1;
    }
    return tmp;
}


Tile &TileIterator::operator*() {
    return _ref.at(_x, _y);
}

Tile &TileIterator::operator->() {
    return _ref.at(_x, _y);
}

TileIterator::TileIterator(const Tile& tile) : _x(tile._pos.x), _y(tile._pos.y), _ref(tile._parent){ }

bool TileIterator::operator==(const TileIterator &second) const {
    if (_x == second._x && _y == second._y)
        return true;
    return false;
}

bool TileIterator::operator!=(const TileIterator &second) const {
    return (!(*this == second));
}

bool TileIterator::operator<(const TileIterator &second) const {
    if (_y < second._y || _x < second._x)
        return true;
    return false;
}

bool TileIterator::operator>(const TileIterator &second) const {
    return (second < *this);
}

bool TileIterator::operator<=(const TileIterator &second) const {
    return (*this == second || *this < second);
}

bool TileIterator::operator>=(const TileIterator &second) const {
    return (*this == second || *this > second);
}

TileIterator &TileIterator::operator=(TileIterator & other) {
    _x = other._x;
    _y = other._y;
    _ref = other._ref;
    return *this;
}

TileIterator::TileIterator(const TileIterator& other) = default;
