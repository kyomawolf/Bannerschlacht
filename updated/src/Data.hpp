#ifndef DATA_HPP
#define DATA_HPP

class Unit;

class Data {
private:
    struct ImageData {

    };
public:
    struct UnitData {
        float       atk;
        float       def;
        int         men;
        float       mov;
        float       mor;
        int          id;
        unsigned int  x; ///pos
        unsigned int  y;
        int      player;
        Unit*   class_d;
    };

    struct MapData {
        unsigned int width;
        unsigned int height;
        //...
    };
protected:
};

#endif /*DATA_HPP*/