#include "map_object/role/monster.h"

Monster::Monster(Position position) : Role(position, 'm') {
    hp_ = 1;
}