#include "map.h"

#include <cassert>
#include <iostream>

Map::Map(int width, int height) {
    map_.resize(height);
    for (auto& row : map_) {
        row.resize(width);
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++)
            vacancies_.insert(Position(i, j));
    }
}

void Map::Print() const {
    for (auto& row : map_) {
        for (const auto& object : row) {
            if (!object) {
                std::cout << ' ' << ' ';
            } else {
                std::cout << ' ' << object->get_symbol();
            }
        }
        std::cout << std::endl;
    }
}

int Map::GetSize() const {
    assert(map_.size() > 0);
    return map_.size() * map_[0].size();
}

std::optional<Position> Map::GetRandomVacancy() const {
    if (vacancies_.empty()) {
        return std::nullopt;
    }
    int index = rand() % vacancies_.size();
    auto it = vacancies_.begin();
    std::advance(it, index);
    return *it;
}

void Map::AddMapObjectToPosition(std::unique_ptr<MapObject> object, Position position) {
    assert(map_[position.x][position.y] == nullptr);
    vacancies_.erase(position);
    map_[position.x][position.y] = std::move(object);
}