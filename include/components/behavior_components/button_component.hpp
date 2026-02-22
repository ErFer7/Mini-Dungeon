#pragma once

#include "components/behavior_components/behavior_component.hpp"
#include "components/graphics_component.hpp"
#include "utils/debug.hpp"
#include "utils/event.hpp"

using utils::Event;
using utils::Handle;
using utils::log_trace;

class ButtonComponent : public BehaviorComponent {
   public:
    typedef Event<> ButtonClickEvent;
    typedef ButtonClickEvent::Listener ButtonClickListener;

   public:
    ButtonComponent(Handle<Entity> entity);

    ButtonComponent(ButtonComponent &&other) : BehaviorComponent(std::move(other)) { this->_move(std::move(other)); }

    ~ButtonComponent() override { log_trace(this, __PRETTY_FUNCTION__); }

    ButtonComponent &operator=(ButtonComponent &&other) {
        BehaviorComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline Handle<ButtonClickEvent> get_on_click_event() {
        return Handle<ButtonClickEvent>(this->_on_click_event.get_id());
    }

    inline void start() override {}

    void update() override;

   private:
    void _move(ButtonComponent &&other) {
        log_trace(this, __PRETTY_FUNCTION__, &other);

        if (this == &other) {
            return;
        }

        this->_on_click_event = std::move(other._on_click_event);
        this->_graphics_component = std::move(other._graphics_component);
    }

   private:
    ButtonClickEvent _on_click_event;
    Handle<GraphicsComponent> _graphics_component;
};
