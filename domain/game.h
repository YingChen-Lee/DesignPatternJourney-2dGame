#pragma once

#include <memory>
#include <unordered_set>

#include "map.h"
#include "map_object/treasure.h"
#include "map_object/obstacle.h"
#include "map_object/role/role.h"
#include "map_object/role/character.h"
#include "map_object/role/monster.h"

/**
 * Game is responsible for :
 * - The game logic
 * - Creating the map and the map objects
 * - The destruction of the map objects
 * - Representing the game state to outer layers
*/
class Game : public Role::RemoveObjectDelegate {
public:
    Game(int width, int height);
    ~Game() override = default;
    void StartRandomGame();

    // Role::RemoveObjectDelegate
    void RemoveObject(MapObject* object) override;
private:
    void Init();
    void PrintCharacterInfo() const;

    std::unique_ptr<Map> map_;
    std::vector<std::unique_ptr<Monster>> monsters_;
    std::unique_ptr<Character> character_ = nullptr;
    std::vector<std::unique_ptr<Treasure>> treasures_;
    std::vector<std::unique_ptr<Obstacle>> obstacles_;

    std::vector<MapObject*> objects_to_remove_;
};