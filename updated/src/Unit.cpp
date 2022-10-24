#include "Unit.hpp"



Unit::Unit(raylib::Texture& init_tex, int init_player, float init_atk, float init_def, int init_men, float init_mov, float init_mor) :
        tex(&init_tex), _atk(init_atk), _def(init_def), _men(init_men), _mov(init_mov), _mor(init_mor), _player(init_player), _id(0)
{

}

Unit::Unit(const UnitData &data) : tex(nullptr), _atk(data.GetAtk()), _def(data.GetDef()), _men(data.GetMen()),
                                         _mov(data.GetMov()), _mor(data.GetMor()), _player(data.GetPlayer()), _id(data.GetId()){ }

int Unit::GetPlayer() const {
    return _player;
}
