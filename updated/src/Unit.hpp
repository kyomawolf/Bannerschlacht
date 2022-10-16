#ifndef PROJEKT_DIESCHLACHT_UNIT_HPP
#define PROJEKT_DIESCHLACHT_UNIT_HPP

#include "raylib-cpp.hpp"
#include "Texture.hpp"
#include "Data.hpp"

class Unit {
public:
    raylib::Texture*    tex = nullptr; //todo make private
    float               scale = 0.02f; //todo make private
private:
    float       _atk;
    float       _def;
    int         _men;
    float       _mov;
    float       _mor;
    int         _player;
    int         _id;
public:
    explicit Unit(raylib::Texture& init_tex, int init_player, float init_atk = 0, float init_def = 0, int init_men = 0, float init_mov = 0, float init_mor = 0);
    Unit(const Data::UnitData& data);
    ~Unit() = default;

};


#endif /*PROJEKT_DIESCHLACHT_UNIT_HPP*/