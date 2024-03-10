#pragma once

#include <cassert>
#include <memory>
#include <string>

class Role;

enum class StateType {
    kNormal,
    kInvincible,
    kPoisoned,
    kAccelerated,
    kHealing,
    kOrderless,
    kStockpile,
    kErupting,
    kTeleport
};

namespace {
std::string StateTypeToString(StateType state_type) {
    switch (state_type) {
        case StateType::kNormal:
            return "Normal";
        case StateType::kInvincible:
            return "Invincible";
        case StateType::kPoisoned:
            return "Poisoned";
        case StateType::kAccelerated:
            return "Accelerated";
        case StateType::kHealing:
            return "Healing";
        case StateType::kOrderless:
            return "Orderless";
        case StateType::kStockpile:
            return "Stockpile";
        case StateType::kErupting:
            return "Erupting";
        case StateType::kTeleport:
            return "Teleport";
        default:
            assert(false && "Unknown StateType");
            return "Unknown";
    }
}
}  // namespace

class State {
public:
    static std::unique_ptr<State> CreateState(StateType state_type, Role* role);

    State(Role* role);
    virtual ~State() = default;

    virtual StateType GetStateType() const = 0;

    /**
     * Upon start the round, the state might need to do some preprocessing
     * e.g. countdown state_round_
     * e.g. gain Hp for healing state
     * The default behavior is to countdown state_round_
     * and enter normal state if state_round_ is 0
    */
    virtual void RoundStartPreprocess();

    /**
     * The role takes a turn.
     * The default behavior is to ask role_ to move or attack.
    */
    virtual void TakeTurn();

    /**
     * The actions to be done when entering and exiting the state
    */
    virtual void EnterState() {};
    virtual void ExitState() {};

    /**
     * The action to be done when the role attacks.
     * The behavior might differ for different states and role types.
    */
    virtual void Attack();

    /**
     * Return whether there is any enemy in the range that the role
     * can attack.
     * @return true if there is an enemy in the range of the role
     * @note only used by Monster. Not implemented for Character
    */
    virtual bool HasEnemyInRange() const;

    /**
     * The action to be done when the role is attacked.
     * E.g. lose HP, enter invincible state, etc.
    */
    virtual void OnAttacked(int damage);

protected:
    // The number of rounds the state can last
    // Note that -1 means the the state can last forever
    int state_round_ = -1;
    Role* role_ = nullptr;
};