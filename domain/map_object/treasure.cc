#include "map_object/treasure.h"

#include <cstdlib>

#include "map_object/role/state/state.h"

// static
std::unique_ptr<Treasure> Treasure::Create(Position position) {
  double random_value = static_cast<double>(rand()) / RAND_MAX;
  double cumulative_probability = 0.0;
  for (int i = 0; i < Treasure::posibility_map.size(); i++) {
    cumulative_probability += Treasure::posibility_map[static_cast<TreasureType>(i)] / 100.0;
    if (random_value < cumulative_probability) {
      return std::make_unique<Treasure>(position, static_cast<TreasureType>(i));
    }
  }
  return std::make_unique<Treasure>(position, TreasureType::kDokoDemoDoor); // just to avoid warning
}

// static
std::map<TreasureType, int> Treasure::posibility_map = {
    {TreasureType::kSuperStar, 10},
    {TreasureType::kPoison, 25},
    {TreasureType::kAcceleratePotion, 20},
    {TreasureType::kHealingPotion, 15},
    {TreasureType::kDevilFruit, 10},
    {TreasureType::kKingsRock, 10},
    {TreasureType::kDokoDemoDoor, 10},
};

void Treasure::ApplyEffect(Role* role) {
  switch (type_) {
    case TreasureType::kSuperStar:
      role->EnterState(StateType::kInvincible);
      break;
    case TreasureType::kPoison:
      role->EnterState(StateType::kPoisoned);
      break;
    case TreasureType::kAcceleratePotion:
      role->EnterState(StateType::kAccelerated);
      break;
    case TreasureType::kHealingPotion:
      role->EnterState(StateType::kHealing);
      break;
    case TreasureType::kDevilFruit:
      role->EnterState(StateType::kOrderless);
      break;
    case TreasureType::kKingsRock:
      role->EnterState(StateType::kStockpile);
      break;
    case TreasureType::kDokoDemoDoor:
      role->EnterState(StateType::kTeleport);
      break;
  }
}