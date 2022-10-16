//
// Created by kyomawolf on 26.08.22.
//

#include <iostream>
#include "Tile.hpp"
#include "Map.hpp"


void Tile::Draw(unsigned int x, unsigned int y) {
//    std::cout << "test" << std::endl;
    if (_initialized) {
        RVector2 pos = Map::LocalToWorld(x, y);
        pos.x += _paddingLeft;
        pos.y += _paddingTop;
//        std::cout << "in here "<< Map::LocalToWorld(x, y) << std::endl;
        _entry->tex->Draw(pos/* plus padding */, 0, _entry->scale);
    }
//    std::cout << "after if" << std::endl;
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
