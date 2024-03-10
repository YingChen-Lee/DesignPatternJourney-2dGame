#include "map_object/role/state/state.h"

#include <cassert>
#include <utility>
#include <vector>

#include "spdlog/spdlog.h"

#include "common.h"
#include "map_object/role/role.h"

// static
std::unique_ptr<State> State::CreateState(StateType state_type, Role* role) {
    switch (state_type) {
        case StateType::kNormal:
            return std::make_unique<NormalState>(role);
        default:
            assert(false && "Unknown StateType");
            return nullptr;
    }
}

State::State(Role* role) : role_(role) {
    assert(role_ != nullptr && "role_ for State::State is nullptr!");
}

void State::RoundStartPreprocess() {
    state_round_--;
    spdlog::debug("{}, role_name_: {}, in state: {}, state_round for this round: {}",
                  __PRETTY_FUNCTION__,
                role_->get_role_name(),
                StateTypeToString(GetStateType()),
                state_round_);
    if (state_round_ == 0) {
        role_->EnterState(StateType::kNormal);
    }
}

void State::TakeTurn() {
    assert(role_ != nullptr && "role_ for State::TakeTurn is nullptr!");
    spdlog::debug("{}, role_name_: {}, take turn in state: {}",
                  __PRETTY_FUNCTION__,
                  role_->get_role_name(),
                  StateTypeToString(GetStateType()));
    role_->MoveOrAttack();
}

void State::Attack() {
    role_->NormalAttack();
    return;
}

bool State::HasEnemyInRange() const {
    if (role_->get_role_type() != RoleType::kMonster) {
        assert(false && "State::HasEnemyInRange() is only implemented for Monster.");
        return false;
    }

    Map* map = role_->get_map();
    Position role_position = role_->get_position();
    const auto neighbor_positions = GetNeighborPositions(role_position);
    for (const Position next_position: neighbor_positions) {
        if (map->IsInRange(next_position)) {
            const MapObject* map_object = map->GetConstMapObjectAtPosition(next_position);
            if (map_object != nullptr && map_object->get_map_object_type() == MapObjectType::kRole) {
                const Role* target_role = dynamic_cast<const Role*>(map_object);
                if (target_role->get_role_type() == RoleType::kCharacter) {
                    spdlog::debug("{}, role: {}, found enemy: {} in Position: {}",
                                  __PRETTY_FUNCTION__,
                                  role_->get_role_name(),
                                  target_role->get_role_name(),
                                  next_position.ToString());
                    return true;
                }
            }
        }
    }
    spdlog::debug("{}, role: {}, no enemy in range",
                  __PRETTY_FUNCTION__,
                  role_->get_role_name());
    return false;
}

void State::OnAttacked(int damage) {
    role_->LoseHp(damage);
    // Enter invincible state
    return;
}