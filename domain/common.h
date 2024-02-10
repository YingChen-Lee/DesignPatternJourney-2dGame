#pragma once

class Position {
public:
    Position(int x, int y) : x(x), y(y) {}
    bool operator<(const Position& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    int x;
    int y;
};
