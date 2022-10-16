#ifndef PROJEKT_DIESCHLACHT_UNIT_HPP
#define PROJEKT_DIESCHLACHT_UNIT_HPP

#include "raylib-cpp.hpp"
#include "Texture.hpp"
#include "data.hpp"

class Unit {
public:
    raylib::Texture*    tex = nullptr;
private:
    float       atk;
    float       def;
    int         men;
    float       mov;
    float       mor;
    int         player;
    int         id;
public:
    float       scale = 0.02f;
    explicit Unit(raylib::Texture& init_tex, int init_player, float init_atk = 0, float init_def = 0, int init_men = 0, float init_mov = 0, float init_mor = 0);
    Unit(const data::UnitData& data);
    ~Unit() = default;

};


#endif /*PROJEKT_DIESCHLACHT_UNIT_HPP*/