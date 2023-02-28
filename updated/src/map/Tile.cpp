//
// Created by kyomawolf on 26.08.22.
//

#include <iostream>

#include "Tile.hpp"
#include "Map.hpp"
#include "../units/Unit.hpp"
#include "../datastructure/Data.hpp"

void Tile::Draw(unsigned int x, unsigned int y) {
        //draw tile terrain

        //draw unit
        RVector2 pos = Map::LocalToWorld(x, y);
        pos.x += _paddingLeft;
        pos.y += _paddingTop;
        auto unit = Data::GetInstance().GetUnitByLocation({x, y});
        if (unit != nullptr) {
            unit->GetTexture().Draw(pos, 0, 0.6f, unit->GetPlayerTints().at(unit->GetPlayer()));
        }
        std::string text = "x: " + std::to_string(x) + " y: " + std::to_string(y);
        raylib::DrawText(text, pos.x, pos.y, 12, raylib::BLACK);
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
TileIterator::TileIterator(const TileIdx &index, Map &ref) : _index(index), _ref(ref){
}

//TileIterator::TileIterator(const TileIdx& index, Map& ref) : _index(index), _ref(ref) {}

void TileIterator::operator++() {
    // std::cout << _index << std::endl;
    if (_index.y >= _ref.GetSize().y) {
        ++_index.x;
        _index.y = 0;
    } else
        ++_index.y;
    // std::cout << _index << std::endl;
}

const TileIterator TileIterator::operator++(int) {
    TileIterator tmp(*this);
    if (_index.y >= _ref.GetSize().y) {
        ++_index.x;
        _index.y = 0;
    } else
        ++_index.y;
    return tmp;
}

void TileIterator::operator--() {
    if (_index.y <= 0) {
        --_index.x;
        _index.y = _ref.GetSize().y - 1;
    } else
        --_index.y;
}

const TileIterator TileIterator::operator--(int) {
    TileIterator tmp(*this);
    if (_index.y <= 0) {
        --_index.x;
        _index.y =  _ref.GetSize().y;
    } else
        --_index.y;
    return tmp;
}


Tile &TileIterator::operator*() {
    return _ref.at(_index);
}

Tile &TileIterator::operator->() {
    return _ref.at(_index);
}

TileIterator::TileIterator(const Tile& tile) : _index(tile._pos), _ref(tile._parent){ }

bool TileIterator::operator==(const TileIterator &second) const {
    if (_index == second._index)
        return true;
    return false;
}

bool TileIterator::operator!=(const TileIterator &second) const {
    return (!(*this == second));
}

bool TileIterator::operator<(const TileIterator &second) const {
    if (_index < second._index)
        return true;
    return false;
}

bool TileIterator::operator>(const TileIterator &second) const {
    return (_index > second._index);
}

bool TileIterator::operator<=(const TileIterator &second) const {
    return (_index <= second._index);
}

bool TileIterator::operator>=(const TileIterator &second) const {
    return (_index >= second._index);
}

TileIterator &TileIterator::operator=(TileIterator & other) {
    _index = other._index;
    _ref = other._ref;
    return *this;
}


TileIterator::TileIterator(const TileIterator& other): _ref(other._ref), _index(other._index) {};


TileIterator::TileIterator(Map& ref) : _ref(ref), _index(0, 0) {}

std::ostream& TileIterator::print(std::ostream& o) const {
    o << "x: " << _index.x << " y: " << _index.y << std::endl;
    return o;
}

std::ostream&    operator<<(std::ostream& o, const TileIterator& printable) {
    return printable.print(o);
}