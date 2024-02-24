#pragma once

#include "map_object/role/state/state.h"

class NormalState : public State {
public:
    NormalState() = default;

    StateType GetStateType() const override;

};