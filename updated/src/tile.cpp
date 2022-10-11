//
// Created by kyomawolf on 26.08.22.
//

#include "tile.hpp"
#include "map.hpp"

void tile::Draw() {
    entry->tex->Draw(map::LocalToWorld(0, 0));
}
