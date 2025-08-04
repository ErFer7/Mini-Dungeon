#pragma once

#include <memory>

#include "./containers/entity_container.hpp"
#include "./managers/behaviour_manager.hpp"
#include "./managers/graphics_manager.hpp"
#include "./managers/main_behaviour_manager.hpp"
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

    inline MainBehaviourManager *get_main_behaviour_manager() { return this->_main_behaviour_manager.get(); };

    inline BehaviourManager *get_behaviour_manager() { return this->_behaviour_manager.get(); };

    inline GraphicsManager *get_graphics_manager() { return this->_graphics_manager.get(); };

    template <typename T = MainBehaviourManager>
    void create_main_behaviour_manager() {
        this->_main_behaviour_manager = std::make_unique<T>(this);
    }

    void init_main_loop();

   private:
    std::unique_ptr<EntityContainer> _entity_container;
    std::unique_ptr<MainBehaviourManager> _main_behaviour_manager;
    std::unique_ptr<BehaviourManager> _behaviour_manager;
    std::unique_ptr<GraphicsManager> _graphics_manager;
};
