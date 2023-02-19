#include "BaseData.hpp"
#include "raylib.hpp"
#include <iostream>
#include "Data.hpp"
#include "../algorithm/PathFinder.hpp"

class Data;
//!     MapData

MapData::MapData(unsigned int initWidth, unsigned int initHeight) : 
                 _width(initWidth), _height(initHeight) {}

MapData::MapData(RVector2 vec) :
                 _width(vec.x), _height(vec.y), _map(vec.y, vec.x) {
    //implement get texture settings from Program settings
}

MapData::MapData() : _width(0), _height(0) {}

void  MapData::SetWidth (unsigned int val) { _width = val; }
void  MapData::SetHeight(unsigned int val) { _height = val; }

unsigned int MapData::GetWidth ( void ) const {return _width;}
unsigned int MapData::GetHeight( void ) const {return _height; }

MapData::~MapData() {

}

Map *MapData::GetMapPointer() {
    return &_map;
}

int MapData::GetIndex() const {
    return _index;
}

void MapData::SetIndex(int index) {
    _index = index;
}

//!     TileData

TileData::TileData(unsigned int initX, unsigned int initY) : _fogow(true), _x(initX), _y(initY) {};
TileData::~TileData() {};

//!     UnitData

UnitData::UnitData() :
        _attack(0), _defense(0), _men(0), _movement(0), _moral(0), _id(0), _position(0, 0),
        _x(0), _y(0), _destination(-1, -1), _player(0), _texture("unit_test_graphic"), _mapUnit(nullptr) {
    _player_tints.emplace_back(0, 0, 255, 255);
    _player_tints.emplace_back(255, 0, 0, 255);
}

UnitData::UnitData(float initAtk, float initDef, int initMen, float initMov, float initMor, int initId,
                   unsigned int initX, unsigned int initY, int initPlayer, const std::shared_ptr<Unit> &initClass_D,
                   const TileIdx& destination, const TileIdx& position) :
        _attack(initAtk), _defense(initDef), _men(initMen), _movement(initMov), _moral(initMor), _id(initId), _position(position),
        _x(initX), _y(initY), _destination(destination), _player(initPlayer), _mapUnit() {
    _mapUnit = initClass_D;
    if (_mapUnit == nullptr)
        std::cerr << "[Warning]: " << "nullpointer init" << std::endl;
    _player_tints.emplace_back(0, 0, 255, 255);
    _player_tints.emplace_back(255, 0, 0, 255);
}

UnitData::~UnitData() {};
///UnitdData Setter

void  UnitData::SetAtk(float val)      { _attack = val; }
void  UnitData::SetDef(float val)      { _defense = val; }
void  UnitData::SetMen(int val)        { _men = val; }
void  UnitData::SetMov(float val)      { _movement = val; }
void  UnitData::SetMor(float val)      { _moral = val; }
void  UnitData::SetId(int val)         { _id = val; }
void  UnitData::SetX(unsigned int val) { _position.x = val; }
void  UnitData::SetY(unsigned int val) { _position.y = val; }
void  UnitData::SetPlayer(int val)     { _player = val; }
void  UnitData::SetMapUnit(std::shared_ptr<Unit>& ptr)  { _mapUnit = ptr; }

///UnitData Getter

float           UnitData::GetAtk     ( void ) const { return _attack; }
float           UnitData::GetDef     ( void ) const { return _defense; }
int             UnitData::GetMen     ( void ) const { return _men; }
float           UnitData::GetMov     ( void ) const { return _movement; }
float           UnitData::GetMor     ( void ) const { return _moral; }
int             UnitData::GetId      ( void ) const { return _id; }
unsigned int    UnitData::GetX       ( void ) const { return _position.x; }
unsigned int    UnitData::GetY       ( void ) const { return _position.y; }
int             UnitData::GetPlayer  ( void ) const { return _player; }
const Unit&     UnitData::GetMapUnit (void ) const { return *_mapUnit; }

UnitData::UnitData(std::shared_ptr<Unit> &rawUnit, const TileIdx& destination, const TileIdx& position)
        : _position(position), _destination(destination), _mapUnit(nullptr) {
    _mapUnit = std::move(rawUnit);
}


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

raylib::Texture& UnitData::GetTexture() {
    return Data::GetInstance().GetTexture(_texture);
}

std::vector<raylib::Color> UnitData::GetPlayerTints() const {
    return _player_tints;
}

//void UnitData::SetDestination0(unsigned x, unsigned y) {
//    _destinationX = x;
//    _destinationY = y;
//}

std::pair<unsigned, unsigned> UnitData::GetDestination0() {
    return std::make_pair(_destinationX, _destinationY);
}

void UnitData::Action() {
    //movement, attack, terrain manipulation, update moral

//    if (_destinationX != _x && _destinationY != _y) {
//        RVector2 next;
//        next = PathFinder::GetNextTile(_x, _y, _destinationX, _destinationY);
//        _x = next.x;
//        _y = next.y;
//    }
}

void UnitData::SetDestination(const TileIdx &destination) {
    _destination = destination;
}

TileIdx UnitData::GetDestination() {
    return _destination;
}

void UnitData::SetPosition(const TileIdx& position) {
    _position = position;
}

TileIdx UnitData::GetPosition() {
    return _position;
}

int UnitData::GetMapIdent() const {
    return _mapIdent;
}

void UnitData::SetMapIdent(int mapIdent) {
    _mapIdent = mapIdent;
}

bool UnitData::IsMoving() const {
    return _moving;
}

void UnitData::SetMoving(bool moving) {
    _moving = moving;
}

bool UnitData::IsAttacking() const {
    return _attacking;
}

void UnitData::SetAttacking(bool attacking) {
    _attacking = attacking;
}
