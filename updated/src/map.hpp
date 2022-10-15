//
// Created by kyomawolf on 26.08.22.
//

#ifndef PROJEKT_DIESCHLACHT_MAP_HPP
#define PROJEKT_DIESCHLACHT_MAP_HPP

#include <string>
#include "raylib-cpp.hpp"
#include "tile.hpp"

class map {
private:
    constexpr static const float size_scaling = 100;
    constexpr static const float image_scaling = 1;
    RVector2 selectedIndex;
    bool     selected;
    raylib::Vector2 size;
    std::vector<std::vector<tile> > field;
public:
    map();
    map(const std::string& file_name);
    map(unsigned int height, unsigned int length);

    void    draw(raylib::Texture& tex);
    raylib::Vector2 positionToIndex(raylib::Vector2& worldPosition);
    bool    OnClick(RVector2 worldPosition);
    static raylib::Vector2 LocalToWorld(unsigned int index_x, unsigned int index_y);
    tile& at(unsigned int x, unsigned int y);
    tile& at(RVector2 pos);
};

#endif //PROJEKT_DIESCHLACHT_MAP_HPP
