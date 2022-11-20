//
// Created by kyomawolf on 26.08.22.
//

#include "Map.hpp"
#include "Tile.hpp"

Map::Map() : _size(10, 10), _field(_size.x) {
    Tile empty;
    Unit std_unit();
    for (auto i = _field.begin(); i != _field.end(); i++) {
        (*i).assign(_size.y, empty);
    }
}

Map::Map(const std::string &file_name) : _size(10, 10), _field(_size.x) {
    Tile empty;
    for (auto i = _field.begin(); i != _field.end(); i++) {
        (*i).assign(_size.y, empty);
    }
}

Map::Map(unsigned int height, unsigned int length) : _size(height, length), _field(_size.x) {
    Tile empty;
        for (auto i = _field.begin(); i != _field.end(); i++) {
            i->assign(_size.y, empty);
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

raylib::Vector2 Map::positionToIndex(raylib::Vector2 &worldPosition) {
    return raylib::Vector2 {floor(worldPosition.x / _sizeScaling), floor(worldPosition.y / _sizeScaling)};
}

raylib::Vector2 Map::LocalToWorld(unsigned int index_x, unsigned int index_y) {
    return {index_x * _sizeScaling, index_y * _sizeScaling};
}

bool Map::OnClick(RVector2 worldPosition) {
    RVector2 indexPos = positionToIndex(worldPosition);
    if (indexPos.x < 0 || indexPos.y < 0 || indexPos.x >= _size.x || indexPos.y >= _size.y)
        return _selected = false;
    if (_selected) {
        at(_selectedIndex).MoveUnit(at(indexPos));
        std:: cout << "moved" << std::endl;
        return _selected = false;
    }
    _selectedIndex = indexPos;
    std::cout << "selected new Tile" << std::endl;
    if (_field[static_cast<int>(_selectedIndex.x)][static_cast<int>(_selectedIndex.y)].GetEntry() != nullptr)
        return _selected = true;
    else
        return _selected = false;
}

Tile &Map::at(RVector2 pos) {
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

Tile * Map::atPosition(RVector2 pos) {
    if (pos.x >= _size.x || pos.y >= _size.y)
        throw std::out_of_range("Map");
    return &_field[floor(pos.x)][floor(pos.y)];
}
