#ifndef PROJEKT_DIESCHLACHT_UNIT_HPP
#define PROJEKT_DIESCHLACHT_UNIT_HPP

#include "raylib.hpp"
#include "Texture.hpp"

class Unit {
public:
    raylib::Texture*    tex = nullptr;
private:
    float       atk = 0;
    float       def = 0;
    int         men = 0;
    float       mov = 0;
    float       mor = 0;
public:
    Unit(raylib::Texture* init_tex, float init_atk, float init_def, int init_men, float init_mov, float init_mor);
    ~Unit() = default;

};


#endif /*PROJEKT_DIESCHLACHT_UNIT_HPP*/