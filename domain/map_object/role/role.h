#pragma once

#include <memory>

#include "map_object/map_object.h"
#include "map_object/role/state/state.h"
#include "map_object/role/state/normal_state.h"

class Role : public MapObject{
public:
    Role(Position position, char symbol);

    // TODO
    void EnterState(StateType state) {};

    bool IsAlive() const;
    int GetHp() const { return hp_; }
    StateType GetStateType() const;

    /*
     * touched_object cannot be a nullptr
     * return true if the touch is valid (i.e. touched_object is not a role)
    */
    bool Touch(MapObject* touched_object);

    // TODO: if surrounded by roles, cannot move, can just skip
    // current round for this role

protected:
    int hp_ = 0;
    std::unique_ptr<State> state_ = nullptr;
};