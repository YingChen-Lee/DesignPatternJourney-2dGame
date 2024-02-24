#pragma once

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

class State {
public:
    State() = default;
    virtual StateType GetStateType() const = 0;
};