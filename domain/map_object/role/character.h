#pragma once

#include<unordered_map>

#include "map_object/role/role.h"



class Character : public Role {
public:
    Character(Position position, Direction direction,
              Role::RemoveObjectDelegate* delegate,
              Map* map);

    // Role
    void Move(std::vector<Direction> available_directions) override;
    void NormalAttack() override;

private:
    static std::unordered_map<Direction, char> direction_to_symbol_;

    bool ChooseToAttack() const override;

    Direction direction_;
};