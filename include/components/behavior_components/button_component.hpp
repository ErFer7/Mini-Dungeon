#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/component.hpp"
#include "components/graphics_component.hpp"
#include "entities/entity.hpp"
#include "utils/debug.hpp"

using utils::log_error;
using utils::log_info;

class ButtonComponent : public BehaviorComponent {
   public:
    typedef Event<> ButtonClickEvent;
    typedef ButtonClickEvent::Listener ButtonClickListener;

   public:
    ButtonComponent(GameCore *game_core, Entity *entity);

    ~ButtonComponent() override { log_info("ButtonComponent::~ButtonComponent()"); }

    inline ButtonClickEvent *get_on_click_event() { return &this->_on_click_event; }

    inline void start() override { log_info("ButtonComponent::start()"); }

    void update() override;

   private:
    ButtonClickEvent _on_click_event;
    GraphicsComponent *_graphics_component;
};
