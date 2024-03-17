#include "map.h"

#include <cassert>
#include <iostream>

#include "spdlog/spdlog.h"

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
    assert(map_.size() > 0 && "map_ is empty!");
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

void Map::AddMapObjectToPosition(MapObject* object, Position position) {
    spdlog::trace("{}, position: {}", __PRETTY_FUNCTION__, position.ToString());
    assert(object != nullptr && "object is nullptr when inserting to map!");
    assert(map_[position.x][position.y] == nullptr && "position is not vacant when inserting an object!");
    vacancies_.erase(position);
    map_[position.x][position.y] = object;
}

const MapObject* Map::GetConstMapObjectAtPosition(Position position) const {
    return map_[position.x][position.y];
}

MapObject* Map::GetMapObjectAtPosition(Position position) {
    return map_[position.x][position.y];
}

bool Map::IsInRange(Position position) const {
    return position.x >= 0 && position.x < map_.size() && position.y >= 0 && position.y < map_[0].size();
}

void Map::RemoveMapObjectAtPosition(Position position) {
    spdlog::debug("{}, position: {}", __PRETTY_FUNCTION__, position.ToString());
    assert(map_[position.x][position.y] != nullptr && "position is vacant when removing an object!");
    vacancies_.insert(position);
    map_[position.x][position.y] = nullptr;
}

void Map::MoveMapObject(MapObject* object, Position next_position) {
    spdlog::debug("{}, position: {}", __PRETTY_FUNCTION__, next_position.ToString());
    assert(IsInRange(next_position) && "next_position is out of range!");
    assert(map_[next_position.x][next_position.y] == nullptr && "next_position is not vacant when moving an object!");
    RemoveMapObjectAtPosition(object->get_position());
    AddMapObjectToPosition(object, next_position);
}