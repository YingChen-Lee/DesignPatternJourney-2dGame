#include "map_object/role/role.h"

#include <cassert>
#include <iostream>

#include "spdlog/spdlog.h"

#include "map_object/treasure.h"

Role::Role(Position position, char symbol,
           Role::RemoveObjectDelegate* delegate,
           Map* map, RoleType role_type)
        : MapObject(position, symbol, MapObjectType::kRole),
          delegate_(delegate), map_(map), role_type_(role_type) {
    state_ = std::move(State::CreateState(StateType::kNormal, this));
    assert(delegate_ != nullptr && "delegate_ for Role::Role is nullptr!");
    assert(map_ != nullptr && "map_ for Role::Role is nullptr!");
}

void Role::EnterState(StateType state) {
    spdlog::debug("{}, role_name_: {}, enter state: {}, leave state: {}",
                  __PRETTY_FUNCTION__, role_name_,
                  StateTypeToString(state),
                  StateTypeToString(state_->GetStateType()));
    state_->ExitState();
    state_ = std::move(State::CreateState(state, this));
    state_->EnterState();
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

        delegate_->RemoveObject(touched_object);
        spdlog::debug("{}, object symbol: {}. Get a treasure of address: {}",
                      __PRETTY_FUNCTION__, get_symbol(), static_cast<void*>(touched_object));
        return true;
    } else {
        spdlog::error("Unknown MapObjectType: {}", static_cast<int>(touched_object->get_map_object_type()));
        assert(false);
        return false;
    }
}

void Role::StartRound() {
    assert(state_ != nullptr && "state_ is nullptr!");
    spdlog::debug("{}, role_name_: {}", __PRETTY_FUNCTION__, role_name_);
    state_->RoundStartPreprocess();
    state_->TakeTurn();
    // TODO
}

void Role::MoveOrAttack() {
    spdlog::debug("{}, role_name_: {}", __PRETTY_FUNCTION__, role_name_);

    // TODO
    if (ChooseToAttack()) {
        //TODO
        state_->Attack();
    } else {
        //TODO
        Move({});
    }
}

void Role::OnAttacked(int damage) {
    state_->OnAttacked(damage);
}

void Role::LoseHp(int lost_hp) {
    hp_ -= lost_hp;
    spdlog::debug("{}, role_name_: {}, lost_hp: {}, new hp: {}",
                  __PRETTY_FUNCTION__, role_name_, lost_hp, hp_);
    if (!IsAlive()) {
        delegate_->RemoveObject(this);
    }
}