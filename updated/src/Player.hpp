//
// Created by Jascha Kasper on 11/6/22.
//

#ifndef BANNERSCHLACHT_PLAYER_HPP
#define BANNERSCHLACHT_PLAYER_HPP

#include "units/Unit.hpp"
#include <vector>

class Player {
private:
    bool    _isCom;
    int     _id = -1;
    std::vector<Unit*>      _vecUnits;
    Unit*       _headquater;
public:
    Player();
    [[nodiscard]] const std::vector<Unit *> &GetVecUnits() const;

    [[nodiscard]] int GetId() const;

    void SetId(int id);

    void AddVecUnits(Unit *unit);

    bool GetIsCom() const;

    void SetIsCom(bool isCom);
    void Routine();
};


#endif //BANNERSCHLACHT_PLAYER_HPP
