//
// Created by kyomawolf on 26.08.22.
//

#ifndef PROJEKT_DIESCHLACHT_TILE_HPP
#define PROJEKT_DIESCHLACHT_TILE_HPP

#include "raylib-cpp.hpp"
#include "Texture.hpp"
#include "Unit.hpp"

class Tile {
private:
    float   _defenceModifier = 1;
    float   _attackModifier = 1;
    bool    _faceAccess[4] = {true, true, true, true}; ///0 = North, 1 = East, 2 = South, 3 = West
    bool    _initialized = false;
    Unit*   _entry = nullptr;
    float   _paddingLeft = 20.0f;
    float   _paddingTop = 20.0f;
public:
    Tile() = default; //uninitialized
//    Tile(...); //initialized
    /// getter and setter for modifier
    raylib::Texture *tileTexture = nullptr;
    void    SetEntry(Unit* new_entry) { _entry = new_entry; _initialized = true; }
    void    SwitchInit()              { _initialized = !_initialized; }
    void    SetInit(bool sw)              { _initialized = sw; }
    Unit*   GetEntry()                { return _entry; }
    float   GetDefenceModifier()    const { return _defenceModifier; };
    float   GetAttackModifier()     const { return _attackModifier; };
    bool    IsBlocked(unsigned int face) { return face >= 4 || _faceAccess[face]; };
    void    Draw(unsigned int x, unsigned int y);
    bool    MoveUnit(Tile& dest);
    bool    GetInit() const;
protected:

};

#endif //PROJEKT_DIESCHLACHT_TILE_HPP
