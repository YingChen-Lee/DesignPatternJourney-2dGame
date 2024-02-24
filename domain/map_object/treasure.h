#pragma once

#include <map>
#include <memory>

#include "map_object/map_object.h"
#include "map_object/role/role.h"

enum class TreasureType {
    kSuperStar,
    kPoison,
    kAcceleratePotion,
    kHealingPotion,
    kDevilFruit,
    kKingsRock,
    kDokoDemoDoor,
};

class Treasure : public MapObject{
public:
    static std::unique_ptr<Treasure> Create(Position position);
    static std::map<TreasureType, int> posibility_map;

    Treasure(Position position, TreasureType type)
            : MapObject(position, '+', MapObjectType::kTreasure), type_(type) {}

    void ApplyEffect(Role* role);
private:
    const TreasureType type_;
};