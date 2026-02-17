#pragma once

#include "components/component.hpp"
#include "components/transform_component.hpp"
#include "definitions.hpp"
#include "raylib.h"
#include "utils/debug.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::log_info;

struct ColliderComponentArgs {
    Rectangle rectangle = Rectangle();
};

// For now this is only a rect collider
class ColliderComponent final : public Component {
    friend class PhysicsComponentManager;

   public:
    ColliderComponent(Handle<Entity> entity, const ColliderComponentArgs &args = ColliderComponentArgs());

    ColliderComponent(ColliderComponent &&other) : Component(std::move(other)) { this->_move(std::move(other)); }

    ~ColliderComponent() override = default;

    ColliderComponent &operator=(ColliderComponent &&other) {
        Component::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    // TODO: Possibly make this private to avoid missuse
    void set_physics_component(Handle<PhysicsComponent> physics_component) {
        this->_physics_component = physics_component;
    }

    bool check_collision(Handle<ColliderComponent> &other) {
        // TODO: Handle collisions with rotated colliders

        // if (DEBUGGED_ON_LOOP) {
        //     log_info(this,
        //              "ColliderComponent: This rect: { x: ",
        //              this->_rectangle.x,
        //              ", y: ",
        //              this->_rectangle.y,
        //              ", width: ",
        //              this->_rectangle.width,
        //              ", height: ",
        //              this->_rectangle.height,
        //              " }, other rect: { x: ",
        //              other->_rectangle.x,
        //              ", y: ",
        //              other->_rectangle.y,
        //              ", width: ",
        //              other->_rectangle.width,
        //              ", height: ",
        //              other->_rectangle.height,
        //              " }");
        // }

        // FIX: The collisions don't work for now
        Vector2Df top_left = Vector2Df(this->_rectangle.x - this->_rectangle.width / 2.0f,
                                       this->_rectangle.y - this->_rectangle.height / 2.0f);
        Vector2Df bottom_right = Vector2Df(this->_rectangle.x + this->_rectangle.width / 2.0f,
                                           this->_rectangle.y + this->_rectangle.height / 2.0f);

        Vector2Df other_top_left = Vector2Df(other->_rectangle.x - other->_rectangle.width / 2.0f,
                                             other->_rectangle.y - other->_rectangle.height / 2.0f);
        Vector2Df other_bottom_right = Vector2Df(other->_rectangle.x + other->_rectangle.width / 2.0f,
                                                 other->_rectangle.y + other->_rectangle.height / 2.0f);

        if (DEBUGGED_ON_LOOP) {
            log_info(this,
                     "ColliderComponent: This TL: ",
                     top_left,
                     ", this BR: ",
                     bottom_right,
                     ", other TL: ",
                     other_top_left,
                     ", other BR: ",
                     other_bottom_right);
        }

        if (top_left.x > other_bottom_right.x || other_top_left.x > bottom_right.x) {
            return false;
        }

        if (bottom_right.y > other_top_left.y || other_bottom_right.y > top_left.y) {
            return false;
        }

        return true;
    }

   private:
    void _move(ColliderComponent &&other) {
        if (this == &other) {
            return;
        }

        this->_rectangle = std::move(other._rectangle);
        this->_transform_component = std::move(other._transform_component);
        this->_transform_update_listener = std::move(other._transform_update_listener);
    }

    void _update_rectangle();

    void _update_rectangle_listener_call(const Vector2Df &, const TransformData &) { this->_update_rectangle(); }

    inline Handle<PhysicsComponent> _get_physics_component() { return this->_physics_component; }

   private:
    Rectangle _rectangle;
    Handle<TransformComponent> _transform_component;
    Handle<PhysicsComponent> _physics_component;
    TransformComponent::TransformUpdateListener _transform_update_listener;
};
