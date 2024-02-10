#pragma once

#include <memory>
#include <optional>
#include <set>
#include <vector>

#include "common.h"
#include "map_object/map_object.h"

class Map {
public:
    Map(int width, int height);
    void Print() const;
    int GetSize() const;
    std::optional<Position> GetRandomVacancy() const;
    void AddMapObjectToPosition(std::unique_ptr<MapObject> object, Position position);

private:
    std::vector<std::vector<std::unique_ptr<MapObject>>> map_;
    std::set<Position> vacancies_;
};
