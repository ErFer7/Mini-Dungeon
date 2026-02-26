#pragma once

#include <type_traits>

#include "containers/asset_containers/font_container.hpp"
#include "containers/asset_containers/image_container.hpp"
#include "containers/asset_containers/texture_container.hpp"
#include "containers/component_containers/heap_allocated_component_container.hpp"
#include "containers/component_containers/stack_allocated_component_container.hpp"
#include "managers/audio_manager.hpp"
#include "managers/behavior_manager.hpp"
#include "managers/game_manager.hpp"
#include "managers/graphics/graphics_manager.hpp"
#include "managers/physics_manager.hpp"
#include "types.hpp"

using utils::IdReferences;

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
        utils::log_trace(nullptr,
                         __PRETTY_FUNCTION__,
                         screen_width,
                         screen_height,
                         title,
                         target_fps,
                         resizable,
                         fullscreen,
                         show_fps);
        _id_references = new IdReferences();
        _instance = new GameCore(screen_height, screen_height, title, target_fps, resizable, fullscreen, show_fps);
    }

    static inline utils::IdReferences *get_id_references() { return _id_references; }

    static inline EntityContainer *get_entity_container() { return _instance->_entity_container.get(); }

    static inline ImageContainer *get_image_container() { return &_instance->_image_container; }

    static inline TextureContainer *get_texture_container() { return &_instance->_texture_container; }

    static inline FontContainer *get_font_container() { return &_instance->_font_container; }

    static inline TransformComponentContainer *get_transform_component_container() {
        return &_instance->_transform_component_container;
    }

    static inline BehaviorComponentContainer *get_behavior_component_container() {
        return &_instance->_behavior_component_container;
    }

    static inline PhysicsComponentContainer *get_physics_component_container() {
        return &_instance->_physics_component_container;
    }

    static inline ColliderComponentContainer *get_collider_component_container() {
        return &_instance->_collider_component_container;
    }

    static inline GraphicsComponentContainer *get_graphics_component_container() {
        return &_instance->_graphics_component_container;
    }

    static inline TextComponentContainer *get_text_component_container() {
        return &_instance->_text_component_container;
    }

    static inline UITransformComponentContainer *get_ui_transform_component_container() {
        return &_instance->_ui_transform_component_container;
    }

    static inline GameManager *get_game_manager() { return &_instance->_game_manager; }

    static inline BehaviorManager *get_behavior_manager() { return &_instance->_behavior_manager; }

    static inline PhysicsManager *get_physics_manager() { return &_instance->_physics_manager; }

    static inline GraphicsManager *get_graphics_manager() { return &_instance->_graphics_manager; }

    static inline AudioManager *get_audio_manager() { return &_instance->_audio_manager; }

    static inline void exit() { _instance->_is_exiting = true; }

    template <typename ComponentType>
    static inline auto *get_component_container() {
        if constexpr (std::is_base_of_v<BehaviorComponent,
                                        ComponentType>) {  // Only BehaviorComponents can be polymorphic
            return &_instance->_behavior_component_container;
        }

        if constexpr (std::is_same_v<ColliderComponent, ComponentType>) {
            return &_instance->_collider_component_container;
        }

        if constexpr (std::is_same_v<GraphicsComponent, ComponentType>) {
            return &_instance->_graphics_component_container;
        }

        if constexpr (std::is_same_v<PhysicsComponent, ComponentType>) {
            return &_instance->_physics_component_container;
        }

        if constexpr (std::is_same_v<TextComponent, ComponentType>) {
            return &_instance->_text_component_container;
        }

        if constexpr (std::is_same_v<TransformComponent, ComponentType>) {
            return &_instance->_transform_component_container;
        }

        if constexpr (std::is_same_v<UITransformComponent, ComponentType>) {
            return &_instance->_ui_transform_component_container;
        }
    }

    static void init_main_loop();

   private:
    static inline GameCore *_instance;

    // TODO: It would be better if this wasn't static
    static inline IdReferences *_id_references;

    std::unique_ptr<EntityContainer> _entity_container;
    ImageContainer _image_container;
    TextureContainer _texture_container;
    FontContainer _font_container;
    TransformComponentContainer _transform_component_container;
    BehaviorComponentContainer _behavior_component_container;
    PhysicsComponentContainer _physics_component_container;
    ColliderComponentContainer _collider_component_container;
    GraphicsComponentContainer _graphics_component_container;
    TextComponentContainer _text_component_container;
    UITransformComponentContainer _ui_transform_component_container;
    GameManager _game_manager;
    BehaviorManager _behavior_manager;
    PhysicsManager _physics_manager;
    GraphicsManager _graphics_manager;
    AudioManager _audio_manager;
    bool _is_exiting;
};
