#include "BaseData.hpp"
#include "raylib.hpp"
#include <iostream>

//!     MapData

MapData::MapData(unsigned int initWidth, unsigned int initHeight) : 
                 _width(initWidth), _height(initHeight) {}

MapData::MapData(RVector2 vec) :
                 _width(vec.x), _height(vec.y) {}

MapData::MapData() : _width(0), _height(0) {}

void  MapData::SetWidth (unsigned int val) { _width = val; }
void  MapData::SetHeight(unsigned int val) { _height = val; }

unsigned int MapData::GetWidth ( void ) const {return _width;}
unsigned int MapData::GetHeight( void ) const {return _height; }

MapData::~MapData() {

}

//!     TileData

TileData::TileData(unsigned int initX, unsigned int initY) : _fogow(true), _x(initX), _y(initY) {};
TileData::~TileData() {};

//!     UnitData

UnitData::UnitData() : 
            _atk(0), _def(0), _men(0), _mov(0), _mor(0), _id(0),
            _x(0),  _y(0), _player(0), _class_d(nullptr) {}

UnitData::UnitData(float initAtk, float initDef, int initMen, 
                   float initMov, float initMor, int initId, 
                   unsigned int initX, unsigned int initY, int initPlayer, 
                   Unit* initClass_D) : 
            _atk(initAtk), _def(initDef), _men(initMen), _mov(initMov), _mor(initMor), _id(initId),
            _x(initX),     _y(initY),     _player(initPlayer),          _class_d(initClass_D) {
    if (_class_d == nullptr)
        std::cerr << "[Warning]: " << "nullpointer init" << std::endl;
}

UnitData::~UnitData() {};
///UnitdData Setter

void  UnitData::SetAtk(float val)      { _atk = val; }
void  UnitData::SetDef(float val)      { _def = val; }
void  UnitData::SetMen(int val)        { _men = val; }
void  UnitData::SetMov(float val)      { _mov = val; }
void  UnitData::SetMor(float val)      { _mor = val; }
void  UnitData::SetId(int val)         { _id = val; }
void  UnitData::SetX(unsigned int val) { _x = val; }
void  UnitData::SetY(unsigned int val) { _y = val; }
void  UnitData::SetPlayer(int val)     { _player = val; }
void  UnitData::SetClass_d(Unit* ptr)  { _class_d = ptr; }

///UnitData Getter

float           UnitData::GetAtk     ( void ) const { return _atk; }
float           UnitData::GetDef     ( void ) const { return _def; }
int             UnitData::GetMen     ( void ) const { return _men; }
float           UnitData::GetMov     ( void ) const { return _mov; }
float           UnitData::GetMor     ( void ) const { return _mor; }
int             UnitData::GetId      ( void ) const { return _id; }
unsigned int    UnitData::GetX       ( void ) const { return _x; }
unsigned int    UnitData::GetY       ( void ) const { return _y; }
int             UnitData::GetPlayer  ( void ) const { return _player; }
Unit*           UnitData::GetClass_d ( void ) const { return _class_d; }


std::ostream& operator<<(std::ostream& o, const UnitData& data) {
    o << "attack:     " << data.GetAtk() << std::endl
      << "defense:    " << data.GetDef() << std::endl
      << "men:        " << data.GetMen() << std::endl
      << "movement:   " << data.GetMov() << std::endl
      << "morale:     " << data.GetMor() << std::endl
      << "id:         " << data.GetId() << std::endl
      << "pos-x:      " << data.GetX() << std::endl
      << "pos-y:      " << data.GetY() << std::endl
      << "player-id:  " << data.GetPlayer() << std::endl;
    return o;
}

BaseData::~BaseData() {

}
