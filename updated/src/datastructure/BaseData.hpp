#ifndef BANNERSCHLACHT_BASEDATA_HPP
#define BANNERSCHLACHT_BASEDATA_HPP
#include "raylib-cpp.hpp"
#include "../map/Map.hpp"
#include "../algorithm/PathFinder.hpp"
#include <iostream>

class Unit;

class BaseData {
public:
    // BaseData() = default;
    virtual ~BaseData();
    virtual void sayHello(){ std::cout << "Hello\n"; }
};

class MapData : public BaseData {
private:
    unsigned int _width;
    unsigned int _height;
    Map          _map;
    int          _index;
public:
    MapData();
    MapData(unsigned int initWidth, unsigned int initHeight);
    MapData(raylib::Vector2 vec);
    ~MapData();
    void  SetWidth (unsigned int val);
    void  SetHeight(unsigned int val);
    void SetIndex(int index);

    int          GetIndex ( void ) const;
    unsigned int GetWidth ( void ) const;
    unsigned int GetHeight( void ) const;
    Map *GetMapPointer();
};

class TileData : public BaseData {
    private:
    bool    _fogow;
    unsigned int _x;
    unsigned int _y;
    public:
    TileData(unsigned int initX, unsigned int initY);
    ~TileData();
    
    
    void SetFogow(bool val);


    bool GetFogow( void ) const;

};

class UnitData : public BaseData {
private:
    int                         _mapIdent = -1;
    float                       _attack;
    float                       _defense;
    int                         _men;
    float                       _movement;
    float                       _moral;
    int                         _id;
    TileIdx                     _position;
    unsigned int                _x; /// current position
    unsigned int                _y;
    TileIdx                     _destination;
    unsigned int                _destinationX; /// destination position
    unsigned int                _destinationY;
    int                         _player;
    std::vector<raylib::Color>  _player_tints;
    std::string                 _texture; //todo make a settings variable

public:
    std::vector<raylib::Color> GetPlayerTints() const;

private:
    std::shared_ptr<Unit>   _mapUnit;
public:
    UnitData();
    UnitData(std::shared_ptr<Unit> &rawUnit, const TileIdx& destination, const TileIdx& position);
    ~UnitData();
    UnitData(float initAtk, float initDef, int initMen, float initMov, float initMor, int initId,
             unsigned int initX, unsigned int initY, int initPlayer, const std::shared_ptr<Unit> &initClass_D,
             const TileIdx& destination, const TileIdx& index);
    void  SetAtk     (float val);
    void  SetDef     (float val);
    void  SetMen     (int val);
    void  SetMov     (float val);
    void  SetMor     (float val);
    void  SetId      (int val);
    void  SetX       (unsigned int val);
    void  SetY       (unsigned int val);
    void  SetPlayer  (int val);
    void  SetMapUnit (std::shared_ptr<Unit>& ptr);
    void  SetDestination(const TileIdx &destination);
    void  SetDestination0 (unsigned x, unsigned y);
    void  SetPosition(const TileIdx& position);
    void  SetMapIdent(int mapIdent);



    float        GetAtk     ( void ) const;
    float        GetDef     ( void ) const;
    int          GetMen     ( void ) const;
    float        GetMov     ( void ) const;
    float        GetMor     ( void ) const;
    int          GetId      ( void ) const;
    unsigned int GetX       ( void ) const;
    unsigned int GetY       ( void ) const;
    int          GetPlayer  ( void ) const;
    const Unit&  GetMapUnit ( void ) const;
    int          GetMapIdent( void ) const;
    std::pair<unsigned, unsigned> GetDestination0();
    raylib::Texture& GetTexture();
    TileIdx  GetDestination();
    TileIdx  GetPosition();

    void    Action();

};

std::ostream& operator<<(std::ostream& o, const UnitData& data);
#endif
