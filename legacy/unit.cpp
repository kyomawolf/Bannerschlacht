#include "unit.hpp"
#include <string>
#include "raylib.h"
#include <iostream> 

unit::unit(int nhp, int nrange, int nmove, int nad) : _max_hp(nhp), _hp(nhp), _range(nrange), _move(nmove), _ad(nad), _moral(100), _multip(1) {}

swordsmen::swordsmen() : unit(100, 1, 2, 20) {}

swordsmen::~swordsmen() {}

void    swordsmen::attack() {
    std::cout << "unit has started an attack";
}