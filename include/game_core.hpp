#pragma once

#include <memory>

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

    ~GameCore();

    inline EntityContainer *get_entity_container() { return this->_entity_container.get(); };

    inline AssetContainer *get_asset_container() { return this->_asset_container.get(); };

    inline GameManager *get_game_manager() { return this->_game_manager.get(); };

    inline BehaviorComponentManager *get_behavior_component_manager() { return this->_behavior_component_manager.get(); };

    inline PhysicsComponentManager *get_physics_component_manager() { return this->_physics_component_manager.get(); };

    inline GraphicsComponentManager *get_graphics_component_manager() { return this->_graphics_component_manager.get(); };

    inline AudioComponentManager *get_audio_component_manager() { return this->_audio_component_manager.get(); };

    void init_main_loop();

   private:
    // TODO: Stop using pointers here
    std::unique_ptr<EntityContainer> _entity_container;
    std::unique_ptr<AssetContainer> _asset_container;
    std::unique_ptr<GameManager> _game_manager;
    std::unique_ptr<BehaviorComponentManager> _behavior_component_manager;
    std::unique_ptr<PhysicsComponentManager> _physics_component_manager;
    std::unique_ptr<GraphicsComponentManager> _graphics_component_manager;
    std::unique_ptr<AudioComponentManager> _audio_component_manager;
};
