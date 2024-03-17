#pragma once

#include <string>
#include <utility>
#include <vector>

class Position {
public:
    Position(int x, int y) : x(x), y(y) {}
    bool operator<(const Position& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    int x;
    int y;
    std::string ToString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

enum class Direction {
    kUp,
    kDown,
    kLeft,
    kRight
};

namespace {
std::vector<Position> GetNeighborPositions(Position position) {
    std::vector<Position> neighbor_positions;

    std::vector<std::pair<int, int>> kDelta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto& [delta_x, delta_y]: kDelta) {
        int next_x = position.x + delta_x;
        int next_y = position.y + delta_y;
        Position next_position(next_x, next_y);
        neighbor_positions.push_back(next_position);
    }
    return neighbor_positions;
}

std::pair<int, int> GetDeltaByDirection(Direction direction) {
    switch (direction) {
        case Direction::kUp:
            return {-1, 0};
        case Direction::kDown:
            return {1, 0};
        case Direction::kLeft:
            return {0, -1};
        case Direction::kRight:
            return {0, 1};
    }
    return {0, 0};
}

std::string DirectionToString(Direction direction) {
    switch (direction) {
        case Direction::kUp:
            return "Up";
        case Direction::kDown:
            return "Down";
        case Direction::kLeft:
            return "Left";
        case Direction::kRight:
            return "Right";
    }
    return "Unknown";
}
}  // namespace