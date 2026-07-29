#pragma once

#include <memory>
#include <unordered_map>

#include "components/collider_component.hpp"
#include "components/physics_component.hpp"
#include "managers/manager.hpp"
#include "managers/physics/collision_group.hpp"
#include "utils/hash.hpp"

using utils::PairHash;

class PhysicsManager final : public Manager {
    friend class PhysicsComponent;

   private:
    typedef std::unordered_map<CollisionGroupPair, CollisionRule, PairHash> CollisionRules;

   public:
    PhysicsManager() = default;

    ~PhysicsManager() override = default;

    void init() override;
    void update() override;
    void exit() override {};

    inline CollisionRule get_collision_rule(Handle<ColliderComponent> collider_a,
                                            Handle<ColliderComponent> collider_b) {
        CollisionGroup group_a = collider_a->get_collision_group();
        CollisionGroup group_b = collider_b->get_collision_group();

        CollisionRule collision_rule = (*this->_collision_rules)[this->_get_collison_group_pair(group_a, group_b)];

        utils::log_warn(this, '[', group_a, ", ", group_b, "]: ", collision_rule);

        return collision_rule != UNDEFINED ? collision_rule : COLLIDE;
    }

    inline void set_collision_rule(CollisionGroup group_a, CollisionGroup group_b, CollisionRule collision_rule) {
        (*this->_collision_rules)[this->_get_collison_group_pair(group_a, group_b)] = collision_rule;
    }

   private:
    inline CollisionGroupPair _get_collison_group_pair(CollisionGroup group_a, CollisionGroup group_b) {
        return group_a < group_b ? CollisionGroupPair(group_a, group_b) : CollisionGroupPair(group_b, group_a);
    }

   private:
    PhysicsComponentContainer *_physics_component_container;
    ColliderComponentContainer *_collider_component_container;
    std::unique_ptr<CollisionRules> _collision_rules;
};
