#pragma once

#include <memory>
#include <unordered_set>

#include "map.h"
#include "map_object/character.h"
#include "map_object/monster.h"

class Game {
public:
    Game(int width, int height);
    void StartRandomGame();
private:
    void Init();

    std::unique_ptr<Map> map_;
    std::unordered_set<Monster*> monsters_;
    Character* character_ = nullptr;
};