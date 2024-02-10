#pragma once

#include "map_object/map_object.h"

class Role : public MapObject{
public:
    Role(Position position, char symbol) : MapObject(position, symbol) {}
};