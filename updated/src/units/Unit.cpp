#include "Unit.hpp"



Unit::Unit(raylib::Texture& init_tex, int init_player, float init_atk, float init_def, int init_men, float init_mov, float init_mor) :
        tex(&init_tex), _atk(init_atk), _def(init_def), _men(init_men), _mov(init_mov), _mor(init_mor), _player(init_player), _id(0)
{

}

Unit::Unit(const UnitData &data) : tex(nullptr), _atk(data.GetAtk()), _def(data.GetDef()), _men(data.GetMen()),
                                         _mov(data.GetMov()), _mor(data.GetMor()), _player(data.GetPlayer()), _id(data.GetId()), _x(data.GetX()), _y(data.GetY()) { }

///UnitdData Setter

void  Unit::SetAtk(float val)      { _atk = val; }
void  Unit::SetDef(float val)      { _def = val; }
void  Unit::SetMen(int val)        { _men = val; }
void  Unit::SetMov(float val)      { _mov = val; }
void  Unit::SetMor(float val)      { _mor = val; }
void  Unit::SetId(int val)         { _id = val; }
void  Unit::SetX(unsigned int val) { _x = val; }
void  Unit::SetY(unsigned int val) { _y = val; }
void  Unit::SetPlayer(int val)     { _player = val; }

///UnitData Getter

float           Unit::GetAtk   () const { return _atk; }
float           Unit::GetDef   () const { return _def; }
int             Unit::GetMen   () const { return _men; }
float           Unit::GetMov   () const { return _mov; }
float           Unit::GetMor   () const { return _mor; }
int             Unit::GetId    () const { return _id; }
unsigned int    Unit::GetX     () const { return _x; }
unsigned int    Unit::GetY     () const { return _y; }
int             Unit::GetPlayer() const { return _player; }

HeadQuarter::HeadQuarter(raylib::Texture &initTex, int initPlayer, float initAtk, float initDef, int initMen,
                         float initMov, float initMor) : Unit(initTex, initPlayer, initAtk, initDef, initMen, initMov,
                                                              initMor) {}
