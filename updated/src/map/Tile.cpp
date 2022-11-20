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

Tile::Tile(int x, int y, Map& parent) : _pos(x, y), _parent(parent) { }

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

TileIterator::TileIterator(TileIterator& other) = default;
