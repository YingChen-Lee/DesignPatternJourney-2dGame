#include "map_object/role/state/normal_state.h"

NormalState::NormalState(Role* role) : State(role) {}

StateType NormalState::GetStateType() const {
    return StateType::kNormal;
}