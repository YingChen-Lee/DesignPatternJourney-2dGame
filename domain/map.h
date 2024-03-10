#pragma once

#include <optional>
#include <set>
#include <vector>

#include "common.h"
#include "map_object/map_object.h"

/**
 * Map is responsible for the information of each position on the map and
 * the information of the map.
 *
 * Map is not responsible for the creation or destruction of MapObjects.
 *
*/
class Map {
public:
    Map(int width, int height);
    void Print() const;
    int GetSize() const;
    std::optional<Position> GetRandomVacancy() const;
    void AddMapObjectToPosition(MapObject* object, Position position);
    const MapObject* GetConstMapObjectAtPosition(Position position) const;
    MapObject* GetMapObjectAtPosition(Position position);
    bool IsInRange(Position position) const;
    void RemoveMapObjectAtPosition(Position position);

private:
    std::vector<std::vector<MapObject*>> map_;
    std::set<Position> vacancies_;
};
