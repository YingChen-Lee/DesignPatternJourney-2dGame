#pragma once

#include "map_object/role.h"

class Character : public Role {
public:
    Character(Position position) : Role(position, '^') {}


};