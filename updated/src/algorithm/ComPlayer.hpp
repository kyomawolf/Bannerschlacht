//
// Created by Jascha Kasper on 11/9/22.
//

#ifndef BANNERSCHLACHT_COMPLAYER_HPP
#define BANNERSCHLACHT_COMPLAYER_HPP
#include "../Player.hpp"

class ComPlayer : public Player {
private:
public:
    ComPlayer();
    ~ComPlayer();
    void    Routine();
};


#endif //BANNERSCHLACHT_COMPLAYER_HPP
