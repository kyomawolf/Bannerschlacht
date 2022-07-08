#pragma once

#include <string>
using namespace std;

class unit {
    private:
    int         _id;
    int         _max_hp;
    int         _hp;//amount of soldiers per unit
    int         _range;
    int         _move;
    double      _ad;//per hp
    double      _multip;
    double      _moral;
    int         _prState;
    
    public:
    unit(int nhp, int nrange, int nmove, int nad);

    int     pbState;

    void    displayStats();
    bool    checkRange();
    void    attack();
    int     takeDmg();

};