#include "map_object/role/monster.h"

#include <vector>

#include "spdlog/spdlog.h"

#include "common.h"

// static
int Monster::counter = 0;

Monster::Monster(Position position, Role::RemoveObjectDelegate* delegate, Map* map)
        : Role(position, 'm', delegate, map, RoleType::kMonster) {
    hp_ = 1;
    Monster::counter++;
    role_name_ = "Monster" + std::to_string(Monster::counter);
}

void Monster::Move(std::vector<Direction> available_directions) {
    // Randomly choose a direction to move
    // The Position should be null or a treasure
    std::vector<Position> available_positions;
    for (const auto& direction : available_directions) {
        int next_x = get_position().x + GetDeltaByDirection(direction).first;
        int next_y = get_position().y + GetDeltaByDirection(direction).second;
        if (!map_->IsInRange(Position(next_x, next_y))) {
            continue;
        }
        MapObject* target = map_->GetMapObjectAtPosition(Position(next_x, next_y));
        if (target == nullptr ||
                target->get_map_object_type() == MapObjectType::kTreasure) {
            available_positions.push_back(Position(next_x, next_y));
        }
    }

    for (const auto& available_position : available_positions) {
        spdlog::trace("{}, role_name_: {}, available_position: {}",
                      __PRETTY_FUNCTION__,
                      get_role_name(),
                      available_position.ToString());
    }

    if (available_positions.empty()) {
        spdlog::debug("{}, role_name_: {}, no available position to move",
                      __PRETTY_FUNCTION__,
                      get_role_name());
        return;
    }

    int random_index = rand() % available_positions.size();
    Position next_position = available_positions[random_index];
    // Touch will be applied, but it's possible that this monster cannot move
    // to that place. Example use case: the place is occupied by an object or
    // the Character.
    bool can_move_to_position = Touch(map_->GetMapObjectAtPosition(next_position));
    if (can_move_to_position) {
        MoveToPosition(next_position);
    }
}

bool Monster::ChooseToAttack() const {
    spdlog::debug("{}, role_name_: {}",
                  __PRETTY_FUNCTION__,
                  get_role_name());
    if (state_->HasEnemyInRange()) {
        return true;
    } else {
        return false;
    }
}

void Monster::NormalAttack() {
    spdlog::debug("{}, role_name_: {}",
                  __PRETTY_FUNCTION__,
                  get_role_name());

    const auto neighbor_positions = GetNeighborPositions(get_position());
    for (const auto& neighbor_position : neighbor_positions) {
        if (!map_->IsInRange(neighbor_position))
            continue;
        MapObject* neighbor = map_->GetMapObjectAtPosition(neighbor_position);
        // Monster attacks Character
        if (neighbor != nullptr && neighbor->get_map_object_type() == MapObjectType::kRole) {
            Role* role = dynamic_cast<Role*>(neighbor);
            if (role->get_role_type() == RoleType::kCharacter) {
                spdlog::debug("{}, role_name_: {} attacks {} by Hp 50",
                              __PRETTY_FUNCTION__,
                              get_role_name(),
                              role->get_role_name());

                role->OnAttacked(50);
            }
        }
    }
    return;
}