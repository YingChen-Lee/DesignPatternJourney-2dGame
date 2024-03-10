#include "game.h"

#include <iostream>
#include "spdlog/spdlog.h"
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

// Temporary helper function to create dummy Monsters or Character for testing purpose
std::unique_ptr<Monster> GenerateDummyMonster(
        Role::RemoveObjectDelegate* delegate, Map* map, Position position) {
    std::unique_ptr<Monster> monster =
            std::make_unique<Monster>(position, delegate, map);
    map->AddMapObjectToPosition(monster.get(), position);
    return std::move(monster);
}

std::unique_ptr<Character>GenerateDummyCharacter(
        Role::RemoveObjectDelegate* delegate, Map* map,
        Position position, Direction direction) {
    std::unique_ptr<Character> character =
            std::make_unique<Character>(position, direction, delegate, map);
    map->AddMapObjectToPosition(character.get(), position);
    return std::move(character);
}
}  // namespace

Game::Game(int width, int height) {
    map_ = std::make_unique<Map>(width, height);
}

void Game::StartRandomGame() {
    auto dummy_monster = GenerateDummyMonster(this, map_.get(), Position(0, 1));
    auto dummy_monster_2 = GenerateDummyMonster(this, map_.get(), Position(0, 3));
    auto dummy_character = GenerateDummyCharacter(this, map_.get(), Position(0, 2), Direction::kLeft);
    dummy_character->StartRound();
    dummy_character->StartRound();
    // Init();
    // PrintCharacterInfo();
    // map_->Print();

    // Start new rounds
    // while (character_->IsAlive() && !monsters_.empty()) {
        // character_->StartRound();
        // reentry_guard_monster = true // prevent from modifying monsters_ in the loop
        // for (auto monster : monsters_) {
        //     if monster is alive
        //     monster->Move();
        //     if character is head
        //          break
        // }
        // reentry_guard_monster = false
        // map_->Print();
        // remove dead monsters
        // remove used treasures
        // generate new treasure, monster
    // }
}

void Game::RemoveObject(MapObject* object) {
    spdlog::debug("{}, object type: {}, object ptr address: {}",
                  __PRETTY_FUNCTION__,
                  MapObjectTypeToString(object->get_map_object_type()),
                  static_cast<void*>(object));
    objects_to_remove_.push_back(object);
    map_->RemoveMapObjectAtPosition(object->get_position());
}

void Game::Init() {
    spdlog::info(__PRETTY_FUNCTION__);
    RandomMapGenerator generator(map_.get());

    character_ = generator.GenerateCharacter(this);
    monsters_ = generator.GenerateMonsters(this);
    treasures_ = generator.GenerateTreasures();
    obstacles_ = generator.GenerateObstacles();
}

void Game::PrintCharacterInfo() const {
    std::cout << "Character's state: "
                << character_->GetStateType()
                << ", HP: " << character_->GetHp() << std::endl;
}