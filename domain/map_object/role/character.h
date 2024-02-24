#pragma once

#include<unordered_map>

#include "map_object/role/role.h"

enum class Direction {
    kUp,
    kDown,
    kLeft,
    kRight
};

class Character : public Role {
public:
    Character(Position position, Direction direction);

private:
    static std::unordered_map<Direction, char> direction_to_symbol_;
    Direction direction_;
};