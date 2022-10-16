#include "unit.hpp"



Unit::Unit(raylib::Texture& init_tex, int init_player, float init_atk, float init_def, int init_men, float init_mov, float init_mor) :
        tex(&init_tex), atk(init_atk), def(init_def), men(init_men), mov(init_mov), mor(init_mor), player(init_player), id(0)
{

}

Unit::Unit(const data::UnitData &data) : tex(nullptr), atk(data.atk), def(data.def), men(data.men),
                                        mov(data.mov), mor(data.mor), player(data.player), id(data.id){ }
