#include "game_core.hpp"

#include <raylib.h>

#include "containers/entity_container.hpp"

GameCore::GameCore(int screen_width,
                   int screen_height,
                   const char *title,
                   int target_fps,
                   bool resizable,
                   bool fullscreen,
                   bool show_fps)
    : _id_references(),
      _entity_container(std::make_unique<EntityContainer>()),
      _texture_container(),
      _image_container(),
      _font_container(),
      _behavior_component_container(),
      _collider_component_container(),
      _graphics_component_container(),
      _physics_component_container(),
      _text_component_container(),
      _transform_component_container(),
      _ui_transform_component_container(),
      _game_manager(),
      _behavior_manager(),
      _physics_manager(),
      _graphics_manager(screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps),
      _is_exiting(false) {
    utils::log_trace(
        this, __PRETTY_FUNCTION__, screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps);
}

void GameCore::init_main_loop() {
    utils::log_trace(_instance, __PRETTY_FUNCTION__);

    _instance->_behavior_manager.init();
    _instance->_physics_manager.init();
    _instance->_graphics_manager.init();
    _instance->_game_manager.init();

    while (!WindowShouldClose() && !_instance->_is_exiting) {
        _instance->_game_manager.update();
        _instance->_behavior_manager.update();
        _instance->_physics_manager.update();
        _instance->_graphics_manager.update();
    }

    _instance->_entity_container->destroy_all_entities();
    _instance->_texture_container.unload_textures();
    _instance->_image_container.unload_images();
    _instance->_font_container.unload_fonts();

    // By this point, all components should be already destroyed

    _instance->_graphics_manager.exit();
    _instance->_behavior_manager.exit();
    _instance->_physics_manager.exit();
    _instance->_game_manager.exit();
}
