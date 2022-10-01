//
// Created by kyomawolf on 26.08.22.
//

#include "map.hpp"
#include "tile.hpp"

map::map() : size(10, 10), field(size.x) {
    tile empty;
    for (auto i = field.begin(); i != field.end(); i++) {
        (*i).assign(size.y, empty);
    }
}

map::map(const std::string &file_name) : size(10, 10), field(size.x) {
    tile empty;
    for (auto i = field.begin(); i != field.end(); i++) {
        (*i).assign(size.y, empty);
    }
}

map::map(unsigned int height, unsigned int length) : size(height, length), field(size.x) {
    tile empty;
    for (auto i = field.begin(); i != field.end(); i++) {
        (*i).assign(size.y, empty);
    }
}

void    map::draw(raylib::Texture& tex) {
    for (unsigned int i = 0; i < field.size(); i++) {
        for (unsigned int ii = 0; ii != field[i].size(); ii++) {
            tex.Draw(raylib::Vector2(i * 100, ii * 100), 0, 1);
        }
    }
}