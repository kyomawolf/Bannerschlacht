//
// Created by kyomawolf on 26.08.22.
//

#include "map.hpp"
#include "tile.hpp"

map::map() : size(10, 10), field(size.x) {
    tile empty;
    Unit std_unit();
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
            field[i][ii].Draw(i, ii);
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

bool map::OnClick(RVector2 worldPosition) {
    RVector2 indexPos = positionToIndex(worldPosition);
    if (indexPos.x >= size.x || indexPos.y >= size.y)
        return selected = false;
    if (selected) {
        at(selectedIndex).MoveUnit(at(indexPos));
        std:: cout << "moved" << std::endl;
        return selected = false;
    } else {
        selectedIndex = indexPos;
        std::cout << "selected new tile" << std::endl;
    }
    return selected = true;
}

tile &map::at(RVector2 pos) {
    if (pos.x >= size.x || pos.y >= size.y)
        throw std::out_of_range("map");
    return field[floor(pos.x)][floor(pos.y)];
}

tile &map::at(unsigned int x, unsigned int y) {
    if (x >= size.x || y >= size.y)
        throw std::out_of_range("map");
    return field[x][y];
}

