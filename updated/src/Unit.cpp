#include "Unit.hpp"



Unit::Unit(raylib::Texture& init_tex, int init_player, float init_atk, float init_def, int init_men, float init_mov, float init_mor) :
        tex(&init_tex), _atk(init_atk), _def(init_def), _men(init_men), _mov(init_mov), _mor(init_mor), _player(init_player), _id(0)
{

}

Unit::Unit(const Data::UnitData &data) : tex(nullptr), _atk(data.atk), _def(data.def), _men(data.men),
                                         _mov(data.mov), _mor(data.mor), _player(data.player), _id(data.id){ }

int Unit::GetPlayer() const {
    return _player;
}
