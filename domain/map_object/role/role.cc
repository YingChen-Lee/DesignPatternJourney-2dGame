#include "map_object/role/role.h"

#include "map_object/treasure.h"

#include <cassert>
#include <iostream>

Role::Role(Position position, char symbol)
        : MapObject(position, symbol, MapObjectType::kRole) {
    state_ = std::make_unique<NormalState>();
}

bool Role::IsAlive() const {
    return hp_ > 0;
}

StateType Role::GetStateType() const {
    assert(state_ != nullptr && "state_ is nullptr!");
    return state_->GetStateType();
}

bool Role::Touch(MapObject* touched_object) {
    assert(touched_object != nullptr && "touched_object is nullptr!");
    if (touched_object->get_map_object_type() == MapObjectType::kRole) {
        std::cout << "Cannot touch a role!" << std::endl;
        return false;
    } else if (touched_object->get_map_object_type() == MapObjectType::kObstacle) {
        std::cout << "Cannot touch a obstacle!" << std::endl;
        return false;
    } else if (touched_object->get_map_object_type() == MapObjectType::kTreasure) {
        // Instead of using Visitor pattern, we use dynamic_cast here for simplicity
        dynamic_cast<Treasure*>(touched_object)->ApplyEffect(this);
        // TODO: remove the treasure from the map
        std::cout << "Get a treasure!" << std::endl;
        return true;
    } else {
        std::cout << "Unknown MapObjectType: " << static_cast<int>(touched_object->get_map_object_type())
                  << std::endl;
        assert(false && "Unknown MapObjectType!");
        return false;
    }
}