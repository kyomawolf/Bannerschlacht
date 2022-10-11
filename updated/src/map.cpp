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
            field[i][ii].Draw();
            tex.Draw(raylib::Vector2(i * size_scaling, ii * size_scaling), 0, image_scaling);
        }
    }
}

raylib::Vector2 map::positionToIndex(raylib::Vector2 &worldPosition) {
    return raylib::Vector2 {floor(worldPosition.x / size_scaling), floor(worldPosition.y / size_scaling)};
}

raylib::Vector2 map::LocalToWorld(unsigned int index_x, unsigned int index_y) {
    return {index_x * size_scaling, index_y * size_scaling};
}
