#pragma once

#include <functional>
#include <unordered_map>

#include "components/behavior_components/behavior_component.hpp"
#include "components/graphics_component.hpp"
#include "raylib.h"
#include "types.hpp"
#include "utils/debug.hpp"

using utils::Handle;
using utils::log_warn;

// TODO: Add comment explaining why there is a instantaneous animation logic and a instantaneous animation call
class AnimationComponent : public BehaviorComponent {
   public:
    typedef int AnimationState;  // TODO: Maybe this isn't the best name (consider the instantaneous animations)
    static const int IDLE = 0;

    // TODO: Maybe make everything const
    struct Animation {
        std::function<void()> _animation;
        // Since raylib uses seconds in double, we will do the same here
        double _duration;
        double _end_time;
        bool _instant_animation;
        AnimationState _next_animation_state;

        Animation()
            : _animation([]() {}),
              _duration(0.0),
              _end_time(0.0),
              _instant_animation(true),
              _next_animation_state(IDLE) {}

        Animation(std::function<void()> &&animation, double duration = 0.0, AnimationState next_animation_state = IDLE)
            : _duration(duration),
              _end_time(0.0),
              _instant_animation(duration == 0.0),
              _next_animation_state(next_animation_state) {
            _animation = animation;
        }

        inline void reset() { this->_end_time = GetTime() + this->_duration; }

        inline bool finished() { return GetTime() >= this->_end_time; }

        inline bool instant_animation() const { return this->_instant_animation; }

        inline AnimationState next_animation_state() const { return this->_next_animation_state; };

        inline void run() { this->_animation(); }
    };

    typedef std::unordered_map<AnimationState, Animation> AnimationMap;

   public:
    AnimationComponent(Handle<Entity> entity);

    AnimationComponent(AnimationComponent &&other) noexcept : BehaviorComponent(std::move(other)) {
        this->_move(std::move(other));
    }

    ~AnimationComponent() override = default;

    inline AnimationComponent &operator=(AnimationComponent &&other) noexcept {
        BehaviorComponent::operator=(std::move(other));
        this->_move(std::move(other));
        return *this;
    }

    // The idea here is that no animation will ever run after its time is up, but we still need to allow instantaneous
    // animations to run once
    // OPTIMIZE: Disable the update for empty animations
    void update() override {
        Animation *current_animation = &this->_animations[this->_current_animation_state];

        if (current_animation->instant_animation()) {
            current_animation->run();
        }

        if (current_animation->finished()) {
            current_animation->reset();
            this->_current_animation_state = current_animation->next_animation_state();

            return;
        }

        current_animation->run();
    }

    // This can be used to run a single animation change without changing the base animation state machine
    inline void run_instantaneous_animation(AnimationState state) {
        Animation *animation = &this->_animations[state];

        if (!animation->instant_animation()) {
            log_warn(this, "AnimationComponent: Attempt to run a continuous animation as a instantaneous animation");
            return;
        }

        animation->run();
    }

    inline void set_animation_state(AnimationState state) {
        this->_current_animation_state = state;
        this->_animations[this->_current_animation_state].reset();
    }

   protected:
    inline Handle<GraphicsComponent> graphics_component() { return this->_graphics_component; }

    // TODO: Find a way to not use this "Type"
    template <typename Type>
    void register_animation(AnimationState state,
                            Handle<Type> handle,
                            void (Type::*method)(),
                            double duration = 0.0,
                            AnimationState next_animation_state = IDLE) {
        this->_animations.insert({state,
                                  Animation(
                                      [handle, method]() {
                                          Type *instance = handle.get_pointer();
                                          if (instance != nullptr) {
                                              (instance->*method)();
                                          }
                                      },
                                      duration,
                                      next_animation_state)});
    }

   private:
    void _move(AnimationComponent &&other) {
        log_trace(this, __PRETTY_FUNCTION__, &other);

        if (this == &other) {
            return;
        }

        this->_current_animation_state = std::move(other._current_animation_state);
        this->_animations = std::move(other._animations);
        this->_graphics_component = std::move(other._graphics_component);
    }

   private:
    AnimationState _current_animation_state;
    AnimationMap _animations;
    Handle<GraphicsComponent> _graphics_component;
};
