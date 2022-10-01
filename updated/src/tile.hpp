//
// Created by kyomawolf on 26.08.22.
//

#ifndef PROJEKT_DIESCHLACHT_TILE_HPP
#define PROJEKT_DIESCHLACHT_TILE_HPP

#include "raylib-cpp.hpp"
#include "Texture.hpp"

#pragma once

class tile {
private:
    float   defence_modifier = 1;
    float   attack_modifier = 1;
    bool    face_access[4] = {true, true, true, true}; ///0 = North, 1 = East, 2 = South, 3 = West
    bool    initialized = false;
public:
    tile() = default; //uninitialized
//    tile(...); //initialized
    /// getter and setter for modifier
    Texture *tileTexture = NULL;
    float   getDefenceModifier()    const { return defence_modifier; };
    float   getAttackModifier()     const { return attack_modifier; };
    bool    is_blocked(unsigned int face) { return face >= 4 || face_access[face]; };
protected:

};

#endif //PROJEKT_DIESCHLACHT_TILE_HPP
