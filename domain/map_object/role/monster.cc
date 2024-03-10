#include "map_object/role/monster.h"

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
    // TODO
    return;
}

bool Monster::ChooseToAttack() const {
    // TODO
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