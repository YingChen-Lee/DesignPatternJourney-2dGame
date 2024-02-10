#include "game.h"

#include "random_map_generator.h"

Game::Game(int width, int height) {
    map_ = std::make_unique<Map>(width, height);
}

void Game::StartRandomGame() {
    Init();
    map_->Print();

}

void Game::Init() {
    RandomMapGenerator generator;

    character_ = generator.GenerateCharacter(map_.get());

    auto monsters = generator.GenerateMonsters(map_.get());
    monsters_.insert(monsters.begin(), monsters.end());

    generator.GenerateTreasures(map_.get());
    generator.GenerateObstacles(map_.get());
}