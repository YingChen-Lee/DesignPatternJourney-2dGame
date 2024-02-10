#pragma once

#include <memory>

#include "map_object/map_object.h"
#include "map_object/role.h"

class Treasure : public MapObject{
public:
    static std::unique_ptr<Treasure> Create(Position position);

    Treasure(Position position) : MapObject(position, '+') {}
};