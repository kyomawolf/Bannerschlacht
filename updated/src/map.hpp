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
    raylib::Vector2 size;
    std::vector<std::vector<tile> > field;
public:
    map();
    map(const std::string& file_name);
    map(unsigned int height, unsigned int length);

    void    draw(raylib::Texture& tex);
    raylib::Vector2 positionToIndex(raylib::Vector2& worldPosition);
};

#endif //PROJEKT_DIESCHLACHT_MAP_HPP
