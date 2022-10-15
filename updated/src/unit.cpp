#include "unit.hpp"



Unit::Unit(raylib::Texture& init_tex, float init_atk, float init_def, int init_men, float init_mov, float init_mor) :
        tex(&init_tex), atk(init_atk), def(init_def), men(init_men), mov(init_mov), mor(init_mor)
{

}
