#pragma once

class Unit;

class BaseData {
public:
    BaseData() = default;
    virtual ~BaseData() = 0;
};

class MapData : BaseData {
private:
    unsigned int _width;
    unsigned int _height;
public:
    MapData();
    MapData(unsigned int initWidth, unsigned int initHeight);
    ~MapData();
    void  SetWidth (unsigned int val);
    void  SetHeight(unsigned int val);

    unsigned int GetWidth ( void ) const;
    unsigned int GetHeight( void ) const;
}

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

}

class UnitData : public BaseData {
private:
    float       _atk;
    float       _def;
    int         _men;
    float       _mov;
    float       _mor;
    int          _id;
    unsigned int  _x; /// pos 
    unsigned int  _y;
    int      _player;
    Unit*   _class_d;
public:
    UnitData();
    ~UnitData();
    UnitData(float initAtk, float initDef, int initMen, 
             float initMov, float initMor, int initId, 
             unsigned int initX, unsigned int initY, int initPlayer, 
             Unit* initClass_D)
    void  SetAtk     (float val);
    void  SetDef     (float val);
    void  SetMen     (int val);
    void  SetMov     (float val);
    void  SetMor     (float val);
    void  SetId      (int val);
    void  SetX       (unsigned int val);
    void  SetY       (unsigned int val);
    void  SetPlayer  (int val);
    void  SetClass_d (Unit* ptr);

    float        GetAtk     ( void ) const;
    float        GetDef     ( void ) const;
    int          GetMen     ( void ) const;
    float        GetMov     ( void ) const;
    float        GetMor     ( void ) const;
    int          GetId      ( void ) const;
    unsigned int GetX       ( void ) const;
    unsigned int GetY       ( void ) const;
    int          GetPlayer  ( void ) const;
    Unit*        GetClass_d ( void ) const;

};