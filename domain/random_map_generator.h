#include <memory>
#include <vector>

#include "common.h"
#include "map.h"
#include "map_object/role/character.h"
#include "map_object/role/monster.h"
#include "map_object/obstacle.h"
#include "map_object/treasure.h"

/**
 * RandomMapGenerator generates monsters, treasures, and obstacles randomly.
 * It gets the vacancies from map when generating map objects.
 * After generating, it will pass the ownership of the objects back to game.
*/
class RandomMapGenerator {
public:
    RandomMapGenerator(Map* map);
    std::vector<std::unique_ptr<Monster>> GenerateMonsters();
    std::unique_ptr<Character> GenerateCharacter();
    std::vector<std::unique_ptr<Treasure>> GenerateTreasures();
    std::vector<std::unique_ptr<Obstacle>> GenerateObstacles();

private:
    Map* map_;
    // rate = 2 means 2/10 chance
    int monster_rate_ = 2;
    int treasure_rate_ = 2;
    int obstacle_rate_ = 2;
};