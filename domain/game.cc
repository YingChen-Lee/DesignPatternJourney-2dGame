#include "game.h"

#include <iostream>
#include <string>

#include "random_map_generator.h"
#include "map_object/role/state/state.h"

namespace {
std::ostream &operator<<(std::ostream &os, const StateType state_type) {
    switch(state_type) {
        case StateType::kNormal:
            os << "Normal";
            break;
        case StateType::kInvincible:
            os << "Invincible";
            break;
        case StateType::kPoisoned:
            os << "Poisoned";
            break;
        case StateType::kAccelerated:
            os << "Accelerated";
            break;
        case StateType::kHealing:
            os << "Healing";
            break;
        case StateType::kOrderless:
            os << "Orderless";
            break;
        case StateType::kStockpile:
            os << "Stockpile";
            break;
        case StateType::kErupting:
            os << "Erupting";
            break;
        case StateType::kTeleport:
            os << "Teleport";
            break;
    }
    return os;
}
}  // namespace

Game::Game(int width, int height) {
    map_ = std::make_unique<Map>(width, height);
}

void Game::StartRandomGame() {
    Init();
    PrintCharacterInfo();
    map_->Print();

    // TODO: can implement Touch first

    // Start new rounds
    // while (character_->IsAlive() && !monsters_.empty()) {
        // character_->Move();
        // reentry_guard_monster = true // prevent from modifying monsters_ in the loop
        // for (auto monster : monsters_) {
        //     monster->Move();
        // }
        // reentry_guard_monster = false
        // map_->Print();
        // remove dead monsters
        // remove used treasures
        // generate new treasure, monster
    // }
}

void Game::RemoveObject(MapObject* object) {
    std::cout << "Remove object: " << object->get_symbol() << std::endl;
    objects_to_remove_.push_back(object);
}

void Game::Init() {
    RandomMapGenerator generator(map_.get());

    character_ = generator.GenerateCharacter();
    monsters_ = generator.GenerateMonsters();
    treasures_ = generator.GenerateTreasures();
    obstacles_ = generator.GenerateObstacles();
}

void Game::PrintCharacterInfo() const {
    std::cout << "Character's state: "
                << character_->GetStateType()
                << ", HP: " << character_->GetHp() << std::endl;
}