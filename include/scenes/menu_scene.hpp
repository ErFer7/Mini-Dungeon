#pragma once

#include "components/behavior_components/button_component.hpp"
#include "scene.hpp"
#include "utils/id/handle.hpp"

using utils::Handle;

class MenuScene final : public Scene {
   public:
    MenuScene() = default;

    ~MenuScene() {};

    void init() override;

    void enter() override {};

    void update() override {};

    void leave() override;

    void exit() override;

   private:
    // This only exists because of the listeners
    void _transition_to_gameplay();

    void _exit();

   private:
    Handle<Background> _background;
    Handle<Text> _title;
    Handle<Text> _version;
    Handle<TextButton> _play_button;
    Handle<TextButton> _exit_button;
    Texture2D _button_texture;
    ButtonComponent::ButtonClickListener _play_listener;
    ButtonComponent::ButtonClickListener _exit_listener;
};
