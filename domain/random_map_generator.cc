#include "random_map_generator.h"

#include <cassert>
#include <iostream>

RandomMapGenerator::RandomMapGenerator(Map* map) : map_(map) {
    // total rate = 10. The rest is vacant.
    assert(monster_rate_ + treasure_rate_ + obstacle_rate_ < 10 && "Total rate should be less than 10");
}

std::vector<std::unique_ptr<Monster>> RandomMapGenerator::GenerateMonsters() {
    std::vector<std::unique_ptr<Monster>> monsters;
    int monster_count = map_->GetSize() * monster_rate_ / 10;
    for (int i = 0; i < monster_count; i++) {
        const auto vacancy = map_->GetRandomVacancy();
        if (!vacancy.has_value()) {
            std::cout << "No vacancy for monster, can only generate "
                      << i << " monsters\n";
            break;
        }
        std::unique_ptr<Monster> monster = std::make_unique<Monster>(vacancy.value());
        map_->AddMapObjectToPosition(monster.get(), vacancy.value());
        monsters.push_back(std::move(monster));
    }
    return monsters;
}

std::unique_ptr<Character> RandomMapGenerator::GenerateCharacter() {
    const auto vacancy = map_->GetRandomVacancy();
    assert(vacancy.has_value() && "No vacancy for character");

    Direction direction = static_cast<Direction>(rand() % 4);
    std::unique_ptr<Character> character = std::make_unique<Character>(vacancy.value(), direction);
    map_->AddMapObjectToPosition(character.get(), vacancy.value());
    return std::move(character);
}

std::vector<std::unique_ptr<Treasure>> RandomMapGenerator::GenerateTreasures() {
    int treasure_count = map_->GetSize() * treasure_rate_ / 10;
    std::vector<std::unique_ptr<Treasure>> treasures;
    for (int i = 0; i < treasure_count; i++) {
        const auto vacancy = map_->GetRandomVacancy();
        if (!vacancy.has_value()) {
            std::cout << "No vacancy for treasure, can only generate "
                      << i << " treasures\n";
            return treasures;
        }
        std::unique_ptr<Treasure> treasure = Treasure::Create(vacancy.value());
        map_->AddMapObjectToPosition(treasure.get(), vacancy.value());
        treasures.push_back(std::move(treasure));
    }
    return treasures;
}

std::vector<std::unique_ptr<Obstacle>> RandomMapGenerator::GenerateObstacles() {
    int obstacle_count = map_->GetSize() * obstacle_rate_ / 10;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    for (int i = 0; i < obstacle_count; i++) {
        const auto vacancy = map_->GetRandomVacancy();
        if (!vacancy.has_value()) {
            std::cout << "No vacancy for obstacle, can only generate "
                      << i << " treasures\n";
            return obstacles;
        }
        std::unique_ptr<Obstacle> obstacle = std::make_unique<Obstacle>(vacancy.value());
        map_->AddMapObjectToPosition(obstacle.get(), vacancy.value());
        obstacles.push_back(std::move(obstacle));
    }
    return obstacles;
}

