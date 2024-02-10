#include <vector>

#include "map.h"
#include "map_object/character.h"
#include "map_object/monster.h"
#include "map_object/obstacle.h"
#include "map_object/treasure.h"

class RandomMapGenerator {
public:
    RandomMapGenerator();
    std::vector<Monster*> GenerateMonsters(Map* map);
    Character* GenerateCharacter(Map* map);
    void GenerateTreasures(Map* map);
    void GenerateObstacles(Map* map);

private:
    // rate = 2 means 2/10 chance
    int monster_rate_ = 2;
    int treasure_rate_ = 2;
    int obstacle_rate_ = 2;
};