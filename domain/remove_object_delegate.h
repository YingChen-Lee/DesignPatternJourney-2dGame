#pragma once

#include "map_object/map_object.h"

/**
 * RemoveObjectDelegate is an interface for removing an object from the game.
 */
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