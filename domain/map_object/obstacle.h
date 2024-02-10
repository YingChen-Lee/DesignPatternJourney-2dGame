#pragma once

#include "map_object/map_object.h"

class Obstacle : public MapObject{
public:
    Obstacle(Position position) : MapObject(position, 'O') {}
};