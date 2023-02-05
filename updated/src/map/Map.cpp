//
// Created by kyomawolf on 26.08.22.
//

#include "Map.hpp"
#include <iostream>
#include "Tile.hpp"
#include "../datastructure/Data.hpp"

Map::Map() : _size(10, 10), _field(_size.x) {
    for (auto i = 0; i < _size.x; i++) {
        for (auto ii = 0; ii < _size.y; ii++) {
            _field[i].push_back({i, ii, *this});
        }
    }
}

Map::Map(unsigned int length, unsigned int height) : _size(length, height), _field(_size.x) {
    for (auto i = 0; i < _size.x; i++) {
        for (auto ii = 0; ii < _size.y; ii++) {
            _field[i].push_back({i, ii, *this});
        }
    }
}

void    Map::Draw(raylib::Texture& tex) {
    for (unsigned int i = 0; i < _field.size(); i++) {
        for (unsigned int ii = 0; ii != _field[i].size(); ii++) {
            _field[i][ii].Draw(i, ii);
            tex.Draw(raylib::Vector2(i * _sizeScaling, ii * _sizeScaling), 0, _imageScaling);
        }
    }
}

TileIdx Map::positionToIndex(TileIdx &worldPosition) {
    return TileIdx { long(floor(worldPosition.x / _sizeScaling)), long(floor(worldPosition.y / _sizeScaling))};
}

raylib::Vector2 Map::LocalToWorld(unsigned int index_x, unsigned int index_y) {
    return {index_x * _sizeScaling, index_y * _sizeScaling};
}

bool Map::OnClick(TileIdx worldPosition) { //todo refactor
    if (Data::GetInstance().GetInput().mouseButton == 2) {
        _selected = false;
        return false;
    }
    TileIdx indexPos = positionToIndex(worldPosition);
    if (indexPos.x < 0 || indexPos.y < 0 || indexPos.x >= _size.x || indexPos.y >= _size.y)
        return _selected = false;
    if (_selected && indexPos != _selectedIndex) {
        auto unit = Data::GetInstance().GetUnitByLocation(_selectedIndex);
        unit->SetDestination0(indexPos.x, indexPos.y);
        // temporary; there will be an implementation of a movement function
        if (Data::GetInstance().GetUnitByLocation(indexPos) != nullptr)
            return _selected = false;
        unit->SetPosition(indexPos);
        unit->SetX(indexPos.x);
        unit->SetY(indexPos.y);
        //        at(_selectedIndex).MoveUnit(at(indexPos));
        std:: cout << "moved" << std::endl;
        return _selected = false;
    }
    _selectedIndex = indexPos;
    std::cout << "selected new Tile" << std::endl;
    auto unit = Data::GetInstance().GetUnitByLocation(indexPos);
    if (unit == nullptr)
        return _selected = false;
    std::cout << unit->GetPlayerTints()[unit->GetPlayer()].r << " " << unit->GetPlayerTints()[unit->GetPlayer()].g << unit->GetPlayerTints()[unit->GetPlayer()].b << std::endl;
    return _selected = true;
//    if (_field[static_cast<int>(_selectedIndex.x)][static_cast<int>(_selectedIndex.y)].GetEntry() != nullptr)
//        return _selected = true;
//    else
//        return _selected = false;
}

Tile &Map::at(TileIdx pos) {
    if (pos.x >= _size.x || pos.y >= _size.y)
        throw std::out_of_range("Map");
    return _field[floor(pos.x)][floor(pos.y)];
}

Tile &Map::at(unsigned int x, unsigned int y) {
    if (x >= _size.x || y >= _size.y)
        throw std::out_of_range("Map");
    return _field[x][y];
}

void Map::Draw() {
    for (unsigned int i = 0; i < _field.size(); i++) {
        for (unsigned int ii = 0; ii != _field[i].size(); ii++) {
            _tileTex->Draw(raylib::Vector2(i * _sizeScaling, ii * _sizeScaling), 0, _imageScaling);
            _field[i][ii].Draw(i, ii);
        }
    }
}

raylib::Texture *Map::GetTileTex() const {
    return _tileTex;
}

void Map::SetTileTex(raylib::Texture *tileTex) {
    Map::_tileTex = tileTex;
}

Tile* Map::atPosition(TileIdx pos) {
    if (pos.x >= _size.x || pos.y >= _size.y)
        throw std::out_of_range("Map");
    return &_field[floor(pos.x)][floor(pos.y)];
}

Map::iterator Map::begin() {
    return {(*_field.begin()->begin())};
}

Map::iterator Map::getIter(int x, int y) {
    return {{x, y}, *this};
}

Map::iterator Map::end() {
    return {{ _size.x, _size.y }, *this};
}

Tile &Map::front() {
    return *begin();
}

Tile &Map::back() {
    iterator it = end();
    --it;
    return (*it);
}

const TileIdx &Map::GetSize() const {
    return _size;
}

void Map::SetSize(const TileIdx &size) {
    _size = size;
}
