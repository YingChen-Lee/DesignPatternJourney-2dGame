#include "map_object/role/character.h"

#include <iostream>

#include "spdlog/spdlog.h"

// static
std::unordered_map<Direction, char> Character::direction_to_symbol_ = {
    {Direction::kUp, '^'},
    {Direction::kDown, 'v'},
    {Direction::kLeft, '<'},
    {Direction::kRight, '>'}
};

Character::Character(Position position, Direction direction,
                     Role::RemoveObjectDelegate* delegate,
                     Map* map) :
        Role(position, direction_to_symbol_[direction],
             delegate, map, RoleType::kCharacter),
        direction_(direction) {
    hp_ = 300;
    role_name_ = "Hero";
}

void Character::Move(std::vector<Direction> available_directions) {
    // TODO
    return;
}

void Character::NormalAttack() {
    spdlog::debug("{}, role_name_: {}",
                  __PRETTY_FUNCTION__,
                  get_role_name());

    const auto [del_x, del_y] = GetDeltaByDirection(direction_);
    int next_x = get_position().x + del_x;
    int next_y = get_position().y + del_y;
    while (map_->IsInRange(Position(next_x, next_y))) {
        MapObject* target = map_->GetMapObjectAtPosition(Position(next_x, next_y));
        if (target != nullptr && target->get_map_object_type() == MapObjectType::kObstacle) {
            break;
        } else if (target != nullptr && target->get_map_object_type() == MapObjectType::kRole) {
            // Character attacks Monster
            Role* target_role = dynamic_cast<Role*>(target);
            if (target_role->get_role_type() == RoleType::kMonster) {
                spdlog::debug("{}, role_name_: {} attacks {}",
                              __PRETTY_FUNCTION__,
                              get_role_name(),
                              target_role->get_role_name());
                target_role->OnAttacked(50);
            }
        }
        next_x += del_x;
        next_y += del_y;
    }
}

bool Character::ChooseToAttack() const {
    std::cout << "Do you want to attack? (y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    if (choice == 'y') {
        return true;
    } else if (choice == 'n') {
        return false;
    } else {
        std::cout << "Invalid input. Please enter y or n." << std::endl;
        return ChooseToAttack();
    }
}