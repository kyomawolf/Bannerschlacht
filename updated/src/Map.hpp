//
// Created by kyomawolf on 26.08.22.
//

#ifndef PROJEKT_DIESCHLACHT_MAP_HPP
#define PROJEKT_DIESCHLACHT_MAP_HPP

#include <string>
#include "raylib-cpp.hpp"
#include "Tile.hpp"

class Map {
private:
    constexpr static const float _sizeScaling = 100;
    constexpr static const float _imageScaling = 1;
    RVector2 _selectedIndex;
    bool     _selected;
    std::vector<std::vector<Tile> > _field;
public:
    raylib::Vector2 _size; //todo make private
    Map();
    Map(const std::string& file_name);
    Map(unsigned int height, unsigned int length);

    void    draw(raylib::Texture& tex);
    raylib::Vector2 positionToIndex(raylib::Vector2& worldPosition);
    bool    OnClick(RVector2 worldPosition);
    static raylib::Vector2 LocalToWorld(unsigned int index_x, unsigned int index_y);
    Tile& at(unsigned int x, unsigned int y);
    Tile& at(RVector2 pos);
};

#endif //PROJEKT_DIESCHLACHT_MAP_HPP
