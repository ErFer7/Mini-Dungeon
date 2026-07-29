#pragma once

#include <utility>

typedef int CollisionGroup;
typedef std::pair<CollisionGroup, CollisionGroup> CollisionGroupPair;

enum : CollisionGroup { NONE, OBSTACLES, DOORS, PLAYER, ENEMIES, PLAYER_ITEMS, ITEMS };

typedef int CollisionRule;

enum : CollisionRule { UNDEFINED = 0, IGNORE = -1, COLLIDE = 1, TRIGGER = 2 };
