#pragma once

#include "map_object/role.h"

class Monster : public Role {
public:
    Monster(Position position) : Role(position, 'm') {}
};