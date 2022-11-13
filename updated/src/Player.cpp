//
// Created by Jascha Kasper on 11/6/22.
//

#include "Player.hpp"

Player::Player() : _vecUnits() {}

const std::vector<Unit *> &Player::GetVecUnits() const {
    return _vecUnits;
}

void Player::AddVecUnits(Unit* newentry) {
    _vecUnits.push_back(newentry);
}

int Player::GetId() const {
    return _id;
}

void Player::SetId(int id) {
    _id = id;
}

bool Player::GetIsCom() const {
    return _isCom;
}

void Player::SetIsCom(bool isAi) {
    _isCom = isAi;
}
