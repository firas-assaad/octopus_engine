#ifndef HPP_COLLISION_RECORD
#define HPP_COLLISION_RECORD

#include <string>
#include <unordered_map>
#include "direction.hpp"

class Map_Object;

// Types of collision events
enum class Collision_Types {
    NONE,           // No collisions found
    NO_MOVE,        // No collisions because this object didn't move
    TILE,           // Tile collision
    OBJECT,         // Object collision: impassable, trigger on key press
    AREA,           // Area collision: passable, automatically trigger
    AREA_OBJECT     // Area Object collision: passable, trigger on key press
};

// Structure returned after collision detection
struct Collision_Record {
    // What triggered this collision
    Collision_Types type;
    // The object that triggered it (usually the player)
    const Map_Object* this_object;
    // The first other object, if any
    Map_Object* other_object;
    // List of objects, for multi-collision
    std::unordered_map<std::string, Map_Object*> other_objects;
    // Direction of edge tiles (e.g. correcting tiles next to a door)
    Direction edge_direction;
    // Does collision type allow passing through?
    bool passable() const {
        return type == Collision_Types::NONE || is_area();
    }
    // Is other object an area?
    bool is_area() const {
        return type == Collision_Types::AREA ||
            type == Collision_Types::AREA_OBJECT;
    }
    // Can other object be triggered by key press?
    bool input_triggerable() const {
        return type == Collision_Types::OBJECT ||
            type == Collision_Types::AREA_OBJECT;
    }
    Collision_Record(Collision_Types type = Collision_Types::NONE,
        const Map_Object* this_object = nullptr,
        Map_Object* other_object = nullptr);
    void set(Collision_Types type, Map_Object* other_object);
};

#endif
