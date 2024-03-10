#pragma once

#include "map_object/role/role.h"

class Monster : public Role {
public:
    static int counter;

    Monster(Position position, Role::RemoveObjectDelegate* delegate,
            Map* map);

    // Role
    void Move(std::vector<Direction> available_directions) override;
    void NormalAttack() override;
private:
    bool ChooseToAttack() const override;
};