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

    ButtonComponent(ButtonComponent &&other) : BehaviorComponent(std::move(other)) { this->_move(std::move(other)); }

    ~ButtonComponent() override { utils::log_trace(this, __PRETTY_FUNCTION__); }

    ButtonComponent &operator=(ButtonComponent &&other) {
        BehaviorComponent::operator=(std::move(other));

        this->_move(std::move(other));

        return *this;
    }

    inline utils::Handle<ButtonClickEvent> get_on_click_event() {
        return utils::Handle<ButtonClickEvent>(this->_on_click_event.get_id());
    }

    inline void start() override {}

    void update() override;

   private:
    void _move(ButtonComponent &&other) {
        if (this == &other) {
            return;
        }

        this->_on_click_event = std::move(other._on_click_event);
        this->_graphics_component = std::move(other._graphics_component);
    }

   private:
    ButtonClickEvent _on_click_event;
    utils::Handle<GraphicsComponent> _graphics_component;
};
