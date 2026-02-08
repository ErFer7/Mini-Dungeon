#pragma once

#include <type_traits>

#include "containers/asset_containers/font_container.hpp"
#include "containers/asset_containers/image_container.hpp"
#include "containers/asset_containers/texture_container.hpp"
#include "containers/component_containers/heap_allocated_component_container.hpp"
#include "containers/component_containers/stack_allocated_component_container.hpp"
#include "containers/entity_container.hpp"
#include "managers/audio_component_manager.hpp"
#include "managers/behavior_component_manager.hpp"
#include "managers/game_manager.hpp"
#include "managers/graphics_component_manager.hpp"
#include "managers/physics_component_manager.hpp"
#include "types.hpp"
#include "utils/id.hpp"

static GameCore *game_core = nullptr;

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

    static void init_game_core(int screen_width,
                               int screen_height,
                               const char *title,
                               int target_fps = 60,
                               bool resizable = false,
                               bool fullscreen = false,
                               bool show_fps = false) {
        game_core = new GameCore(screen_height, screen_height, title, target_fps, resizable, fullscreen, show_fps);
    }

    static GameCore *get_instance() { return game_core; }

    inline EntityContainer *get_entity_container() { return &this->_entity_container; };

    inline ImageContainer *get_image_container() { return &this->_image_container; };

    inline TextureContainer *get_texture_container() { return &this->_texture_container; };

    inline FontContainer *get_font_container() { return &this->_font_container; };

    inline BehaviorComponentContainer *get_behavior_component_container() {
        return &this->_behavior_component_container;
    }

    inline GameManager *get_game_manager() { return &this->_game_manager; };

    inline BehaviorComponentManager *get_behavior_component_manager() { return &this->_behavior_component_manager; };

    inline PhysicsComponentManager *get_physics_component_manager() { return &this->_physics_component_manager; };

    inline GraphicsComponentManager *get_graphics_component_manager() { return &this->_graphics_component_manager; };

    inline AudioComponentManager *get_audio_component_manager() { return &this->_audio_component_manager; };

    inline utils::IdReferences *get_id_references() { return &this->_id_references; }

    template <typename ComponentType>
    auto *get_component_container() const;

    inline void exit() { this->_is_exiting = true; }

    void init_main_loop();

   private:
    EntityContainer _entity_container;
    ImageContainer _image_container;
    TextureContainer _texture_container;
    FontContainer _font_container;
    BehaviorComponentContainer _behavior_component_container;
    ColliderComponentContainer _collider_component_container;
    GraphicsComponentContainer _graphics_component_container;
    PhysicsComponentContainer _physics_component_container;
    TextComponentContainer _text_component_container;
    TransformComponentContainer _transform_component_container;
    UITransformComponentContainer _ui_transform_component_container;
    GameManager _game_manager;
    BehaviorComponentManager _behavior_component_manager;
    PhysicsComponentManager _physics_component_manager;
    GraphicsComponentManager _graphics_component_manager;
    AudioComponentManager _audio_component_manager;
    utils::IdReferences _id_references;
    bool _is_exiting;
};
