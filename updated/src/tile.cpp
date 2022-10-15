//
// Created by kyomawolf on 26.08.22.
//

#include <iostream>
#include "tile.hpp"
#include "map.hpp"


void tile::Draw(unsigned int x, unsigned int y) {
//    std::cout << "test" << std::endl;
    if (initialized) {
        RVector2 pos = map::LocalToWorld(x, y);
        pos.x += padding_left;
        pos.y += padding_top;
//        std::cout << "in here "<< map::LocalToWorld(x, y) << std::endl;
        entry->tex->Draw(pos/* plus padding */, 0, entry->scale);
    }
//    std::cout << "after if" << std::endl;
}

bool tile::MoveUnit(tile &dest) {
    if (dest.GetEntry() != nullptr || entry == nullptr)
        return false;
    dest.SetEntry(entry);
    entry = nullptr;
    initialized = false;
    dest.SetInit(true);
    std::cout << "success" << std::endl;
    return true;
}
