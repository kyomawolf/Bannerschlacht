//
// Created by Jascha Kasper on 11/6/22.
//

#include "Player.hpp"
#include "datastructure/Data.hpp"
#include "algorithm/PathFinder.hpp"

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


// todo make member
static void MoveUnits(int id) {
    Pathfinder& local = Data::GetInstance().GetPathfinder();
    auto unitCollectionLocal = Data::GetInstance().GetUnitCollection();
    for (auto& idx : unitCollectionLocal) {
        if (idx->GetPlayer() != id || !idx->IsMoving())
            continue;
        auto path = local.GeneratePath(idx->GetPosition(), idx->GetDestination());
        // todo simplify
        bool flag = false;
        for (auto& idxTiles : path._usedTiles) {
            std::cout << idxTiles << std::endl;
            if (flag && idxTiles != path._start) {
                std::cout << "next tile ^" << std::endl;
                idx->SetPosition(idxTiles);
                if (idx->GetPosition() == path._end)
                    idx->SetMoving(false);
                break;
            }
            else if (!flag && idxTiles == path._start) {
                std::cout << "flag tile ^" << std::endl;
                flag = true;
            }
        }
    }
}

void Player::Routine() {
    std::cout << "routine called for " << GetId() << std::endl;
    MoveUnits(GetId());
}
