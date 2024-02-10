#include "random_map_generator.h"

#include <cassert>
#include <iostream>

RandomMapGenerator::RandomMapGenerator() {
    // total rate = 10. The rest is vacant.
    assert(monster_rate_ + treasure_rate_ + obstacle_rate_ < 10);
}

std::vector<Monster*> RandomMapGenerator::GenerateMonsters(Map* map) {
    std::vector<Monster*> monsters;
    int monster_count = map->GetSize() * monster_rate_ / 10;
    for (int i = 0; i < monster_count; i++) {
        const auto vacancy = map->GetRandomVacancy();
        if (!vacancy.has_value()) {
            std::cout << "No vacancy for monster\n";
            break;
        }
        std::unique_ptr<Monster> monster = std::make_unique<Monster>(vacancy.value());
        monsters.push_back(monster.get());
        map->AddMapObjectToPosition(std::move(monster), vacancy.value());
    }
    return monsters;
}

Character* RandomMapGenerator::GenerateCharacter(Map* map) {
    const auto vacancy = map->GetRandomVacancy();
    if (!vacancy.has_value()) {
        std::cout << "No vacancy for character\n";
        return nullptr;
    }
    std::unique_ptr<Character> character = std::make_unique<Character>(vacancy.value());
    Character* character_ptr = character.get();
    map->AddMapObjectToPosition(std::move(character), vacancy.value());
    return character_ptr;
}

void RandomMapGenerator::GenerateTreasures(Map* map) {
    int treasure_count = map->GetSize() * treasure_rate_ / 10;
    for (int i = 0; i < treasure_count; i++) {
        const auto vacancy = map->GetRandomVacancy();
        if (!vacancy.has_value()) {
            std::cout << "No vacancy for treasure\n";
            return;
        }
        std::unique_ptr<Treasure> treasure = Treasure::Create(vacancy.value());
        map->AddMapObjectToPosition(std::move(treasure), vacancy.value());
    }
}

void RandomMapGenerator::GenerateObstacles(Map* map) {
    int obstacle_count = map->GetSize() * obstacle_rate_ / 10;
    for (int i = 0; i < obstacle_count; i++) {
        const auto vacancy = map->GetRandomVacancy();
        if (!vacancy.has_value()) {
            std::cout << "No vacancy for obstacle\n";
            return;
        }
        std::unique_ptr<Obstacle> obstacle = std::make_unique<Obstacle>(vacancy.value());
        map->AddMapObjectToPosition(std::move(obstacle), vacancy.value());
    }
}

