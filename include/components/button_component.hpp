#pragma once

#include "../entities/entity.hpp"
#include "../types.hpp"
#include "behavior_component.hpp"
#include "component.hpp"
#include "graphics_component.hpp"
#include "utils/event.hpp"

class ButtonComponent : public BehaviorComponent {
   public:
    typedef Event<> ButtonClickEvent;
    typedef ButtonClickEvent::Listener ButtonClickListener;

   public:
    ButtonComponent(GameCore *game_core, Entity *entity);

    ~ButtonComponent() override {}

    inline ButtonClickEvent *get_on_click_event() { return &this->_on_click_event; }

    inline void start() override {}

    void update() override;

   private:
    ButtonClickEvent _on_click_event;
    GraphicsComponent *_graphics_component;
};
