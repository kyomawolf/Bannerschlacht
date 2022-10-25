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
    unsigned int  _x = 0; /// pos
    unsigned int  _y = 0;
public:
    raylib::Color player_tints[2] = { {255, 255, 255, 255}, {50, 50, 255, 255} };
    explicit Unit(raylib::Texture& init_tex, int init_player, float init_atk = 0, float init_def = 0, int init_men = 0, float init_mov = 0, float init_mor = 0);
    Unit(const UnitData& data);
    ~Unit() = default;
    void  SetAtk     (float val);
    void  SetDef     (float val);
    void  SetMen     (int val);
    void  SetMov     (float val);
    void  SetMor     (float val);
    void  SetId      (int val);
    void  SetX       (unsigned int val);
    void  SetY       (unsigned int val);
    void  SetPlayer  (int val);

    [[nodiscard]] float        GetAtk     ( void ) const;
    [[nodiscard]] float        GetDef     ( void ) const;
    [[nodiscard]] int          GetMen     ( void ) const;
    [[nodiscard]] float        GetMov     ( void ) const;
    [[nodiscard]] float        GetMor     ( void ) const;
    [[nodiscard]] int          GetId      ( void ) const;
    [[nodiscard]] unsigned int GetX       ( void ) const;
    [[nodiscard]] unsigned int GetY       ( void ) const;
    [[nodiscard]] int          GetPlayer  ( void ) const;
};


#endif /*PROJEKT_DIESCHLACHT_UNIT_HPP*/