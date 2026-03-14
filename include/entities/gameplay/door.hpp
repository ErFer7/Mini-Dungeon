#pragma once

#include "components/behavior_components/door_component.hpp"
#include "entities/entity2D.hpp"
#include "entities/static_physical_entity2D.hpp"
#include "utils/vector.hpp"

using utils::Handle;
using utils::Vector2Df;

struct DoorArgs {
    Texture2D texture;
    RenderingMode rendering_mode;
    Vector2Df position = Vector2Df();
    float rotation = 0.0f;
    Vector2Df scale = Vector2Df(1.0f);
    Color color = WHITE;
    int layer = 0;
    Rectangle collider_rectangle = Rectangle();
    float texture_scale = VIRTUAL_SCALE;
    Room *target_room = nullptr;
    Vector2Df exit_position = Vector2Df();

    operator StaticPhysicalEntity2DArgs() const {
        return StaticPhysicalEntity2DArgs{
            texture, rendering_mode, position, rotation, scale, color, layer, texture_scale, true, collider_rectangle};
    }

    operator DoorComponentArgs() const {
        return DoorComponentArgs{target_room, exit_position};
    }
};

class Door final : public StaticPhysicalEntity2D {
   public:
    Door(const DoorArgs &args);

    ~Door() override = default;

    inline Handle<DoorComponent> get_door_component() { return this->_door_component; }

   private:
    Handle<DoorComponent> _door_component;
};
