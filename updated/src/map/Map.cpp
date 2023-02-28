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
    //deselect unit
    if (Data::GetInstance().GetInput().mouseButton == 2) {
        _selected = false;
        return false;
    }
    //get position
    TileIdx indexPos = positionToIndex(worldPosition);
    //check for boundaries
    if (indexPos.x < 0 || indexPos.y < 0 || indexPos.x >= _size.x || indexPos.y >= _size.y)
        return _selected = false;
    //movement if already selected
    if (_selected && indexPos != _selectedIndex) {
        auto unit = Data::GetInstance().GetUnitByLocation(_selectedIndex);
        std::cout << unit << std::endl;
//        unit->SetDestination0(indexPos.x, indexPos.y);
        unit->SetDestination({indexPos.x, indexPos.y});
        unit->SetMoving(true);
        // temporary; there will be an implementation of a movement function
        if (Data::GetInstance().GetUnitByLocation(indexPos) != nullptr)
            return _selected = false;
//        unit->SetPosition(indexPos);
//        unit->SetX(indexPos.x);
//        unit->SetY(indexPos.y);
        //        at(_selectedIndex).MoveUnit(at(indexPos));
        std:: cout << "moved" << std::endl;
        return _selected = false; /// bad formatting right here; if possible reduce to one return statement
    }
    //select unit if none is selected right now
    _selectedIndex = indexPos;
    std::cout << "selected new Tile" << std::endl;
    auto unit = Data::GetInstance().GetUnitByLocation(indexPos);
    if (unit == nullptr)
        return _selected = false;
    std::cout << "owner: " << unit->GetPlayer() << std::endl;
//    std::cout << unit->GetPlayerTints()[unit->GetPlayer()].r << " " << unit->GetPlayerTints()[unit->GetPlayer()].g << unit->GetPlayerTints()[unit->GetPlayer()].b << std::endl;
    return _selected = true;
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
    return {{ _size.x, 0 }, *this};
}

Tile &Map::front() {
    return *begin(); //highly fucking illegal i think
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
