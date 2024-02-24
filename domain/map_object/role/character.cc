#include "map_object/role/character.h"

// static
std::unordered_map<Direction, char> Character::direction_to_symbol_ = {
    {Direction::kUp, '^'},
    {Direction::kDown, 'v'},
    {Direction::kLeft, '<'},
    {Direction::kRight, '>'}
};

Character::Character(Position position, Direction direction) :
        Role(position, direction_to_symbol_[direction]),
        direction_(direction) {
    hp_ = 300;
}