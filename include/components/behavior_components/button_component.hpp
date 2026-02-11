#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/graphics_component.hpp"
#include "utils/debug.hpp"
#include "utils/event.hpp"

class ButtonComponent : public BehaviorComponent {
   public:
    typedef utils::Event<> ButtonClickEvent;
    typedef ButtonClickEvent::Listener ButtonClickListener;

   public:
    ButtonComponent(Entity *entity);

    ~ButtonComponent() override { utils::log_trace(__FUNCTION__); }

    inline ButtonClickEvent *get_on_click_event() { return &this->_on_click_event; }

    inline void start() override {}

    void update() override;

   private:
    ButtonClickEvent _on_click_event;
    utils::Handle<GraphicsComponent> _graphics_component;
};
