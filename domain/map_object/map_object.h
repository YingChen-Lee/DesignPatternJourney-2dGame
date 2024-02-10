#pragma once

#include "common.h"

class MapObject {
public:
    MapObject(Position position, char symbol) : position_(position), symbol_(symbol) {}
    Position get_position() const { return position_; }
    void set_position(Position position) { position_ = position; }
    char get_symbol() const { return symbol_; }

protected:
    void set_symbol(char symbol) { symbol_ = symbol; }

private:
    Position position_;
    char symbol_;
};