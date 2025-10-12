#pragma once

#include "components/behavior_components/button_component.hpp"
#include "entities/user_interface/background.hpp"
#include "entities/user_interface/text.hpp"
#include "entities/user_interface/text_button.hpp"
#include "scene.hpp"

class MenuScene : public Scene {
   public:
    MenuScene() = default;

    MenuScene(GameCore *game_core) : Scene(game_core){};

    ~MenuScene(){};

    void init() override;

    void enter() override {};

    void update() override {};

    void leave() override;

    void exit() override;

   private:
    Background *_background;
    Text *_title;
    Text *_version;
    TextButton *_play_button;
    TextButton *_exit_button;
    Texture2D _button_texture;
    ButtonComponent::ButtonClickListener _play_listener;
    ButtonComponent::ButtonClickListener _exit_listener;
};
