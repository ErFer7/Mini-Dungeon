#pragma once

#include "./containers/asset_container.hpp"
#include "./containers/entity_container.hpp"
#include "./managers/audio_component_manager.hpp"
#include "./managers/behavior_component_manager.hpp"
#include "./managers/game_manager.hpp"
#include "./managers/graphics_component_manager.hpp"
#include "./managers/physics_component_manager.hpp"
#include "types.hpp"

class GameCore {
   public:
    GameCore() = default;

    GameCore(int screen_width,
             int screen_height,
             const char *title,
             int target_fps = 60,
             bool resizable = false,
             bool fullscreen = false,
             bool show_fps = false);

    ~GameCore() = default;

    inline EntityContainer *get_entity_container() { return &this->_entity_container; };

    inline AssetContainer *get_asset_container() { return &this->_asset_container; };

    inline GameManager *get_game_manager() { return &this->_game_manager; };

    inline BehaviorComponentManager *get_behavior_component_manager() { return &this->_behavior_component_manager; };

    inline PhysicsComponentManager *get_physics_component_manager() { return &this->_physics_component_manager; };

    inline GraphicsComponentManager *get_graphics_component_manager() { return &this->_graphics_component_manager; };

    inline AudioComponentManager *get_audio_component_manager() { return &this->_audio_component_manager; };

    inline void exit() { this->_is_exiting = true; }

    void init_main_loop();

   private:
    EntityContainer _entity_container;
    AssetContainer _asset_container;
    GameManager _game_manager;
    BehaviorComponentManager _behavior_component_manager;
    PhysicsComponentManager _physics_component_manager;
    GraphicsComponentManager _graphics_component_manager;
    AudioComponentManager _audio_component_manager;
    bool _is_exiting;
};
