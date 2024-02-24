#pragma once

#include "common.h"

enum class MapObjectType {
    kRole,
    kObstacle,
    kTreasure
};

class MapObject {
public:
    MapObject(Position position, char symbol, MapObjectType type)
            : position_(position), symbol_(symbol), map_object_type_(type) {}
    virtual ~MapObject() = default;
    Position get_position() const { return position_; }
    void set_position(Position position) { position_ = position; }
    char get_symbol() const { return symbol_; }
    MapObjectType get_map_object_type() const { return map_object_type_; }

protected:
    void set_symbol(char symbol) { symbol_ = symbol; }

private:
    Position position_;
    char symbol_;
    MapObjectType map_object_type_;
};