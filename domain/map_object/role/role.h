#pragma once

#include <memory>
#include <string>
#include <vector>

#include "common.h"
#include "map.h"
#include "map_object/map_object.h"
#include "map_object/role/state/state.h"
#include "map_object/role/state/normal_state.h"

enum class RoleType {
    kMonster,
    kCharacter
};

class Role : public MapObject{
public:
    class RemoveObjectDelegate {
    public:
        /**
          * Removes the object from the game and the map.
          * Note that the object might not be deleted immediately.
          * It might be deleted after the current round.
          * After removed, the object will not appear in the map.
        */
        virtual void RemoveObject(MapObject* object_to_remove) = 0;
        virtual ~RemoveObjectDelegate() = default;
    };

    Role(Position position, char symbol,
         Role::RemoveObjectDelegate* delegate,
         Map* map,
         RoleType role_type);

    void EnterState(StateType state);

    bool IsAlive() const;
    int GetHp() const { return hp_; }
    StateType GetStateType() const;
    std::string get_role_name() const { return role_name_; }
    RoleType get_role_type() const { return role_type_; }

    Map* get_map() const { return map_; }

    /**
     * touched_object can be a nullptr, but nothing will happen.
     * @note The touched_object might be removed from the map.
     * @return true if the role can move to the position, false otherwise.
     *         E.g. if touched_object is a role or an obstacle, return false.
     *              if touched_object is a treasure or null, return true.
    */
    bool Touch(MapObject* touched_object);

    /**
     * The role starts a new round.
     * The behavior might be different based on the current state.
    */
    void StartRound();

    /**
     * The template function for the role to move or attack.
     * @note Should only be called by State
    */
    void MoveOrAttack();

    /**
     * @return true if the role chooses to attack, false if the role chooses to move
    */
    virtual bool ChooseToAttack() const = 0;

    /**
     * From one of the available directions, the role can choose
     * where to move.
     * @param available_directions The directions the role can move to
     * @note If no available directions, the role will not move.
     * @note It's not guaranteed that the role will be able to move to
     *       the direction, because there might be obstacles or other roles.
    */
    virtual void Move(std::vector<Direction> available_directions) = 0;

    /**
     * Force the role to move to a certain position.
     *
     * No action will be taken if:
     * - If the position is occupied by another role or an obstacle.
     * - If the position is out of range.
     *
     * Action will be taken if:
     *
     * @param position The position the role will move to.
    */
    void MoveToPosition(Position position);

    /**
     * The default way for the role to attack.
    */
    virtual void NormalAttack() = 0;

    /**
     * Attacked by other roles by a certain amount of damage.
     * The effect might be different based on the current state.
     * @param damage The amount of damage the role is attacked by. The exact
     *       effect might not be the same as the Hp lost.
     * @note The role will be removed from the game if the
     *       hp is less than or equal to 0.
     * @note The role is responsible for removing itself from the map.
     *       @ref Role::LoseHp() is responsible for removing itself from
     *       the map if the role is dead.
    */
    void OnAttacked(int damage);

    /**
     * The role loses a certain amount of Hp.
     * @param lost_hp The amount of Hp the role loses.
     * @note The role might remove itself from the map after it's dead.
    */
    void LoseHp(int lost_hp);

    // TODO: if surrounded by roles, cannot move, can just skip
    // current round for this role

protected:
    int hp_ = 0;
    std::unique_ptr<State> state_ = nullptr;

    // Delegate to remove the object from the game
    Role::RemoveObjectDelegate* delegate_ = nullptr;

    std::string role_name_ = "";
    RoleType role_type_;

    Map* map_ = nullptr;
};