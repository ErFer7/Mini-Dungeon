#include "game_core.hpp"

#include <raylib.h>

#include <type_traits>

#include "containers/entity_container.hpp"

GameCore::GameCore(int screen_width,
                   int screen_height,
                   const char *title,
                   int target_fps,
                   bool resizable,
                   bool fullscreen,
                   bool show_fps)
    : _entity_container(std::make_unique<EntityContainer>()),
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
      _behavior_component_manager(),
      _physics_component_manager(),
      _graphics_component_manager(screen_width, screen_height, title, target_fps, resizable, fullscreen, show_fps),
      _id_references(),
      _is_exiting(false) {}

void GameCore::init_main_loop() {
    this->_behavior_component_manager.init();
    this->_physics_component_manager.init();
    this->_graphics_component_manager.init();
    this->_game_manager.init();

    while (!WindowShouldClose() && !_is_exiting) {
        this->_game_manager.update();
        this->_behavior_component_manager.update();
        this->_physics_component_manager.update();
        this->_graphics_component_manager.update();
    }

    this->_entity_container->destroy_all_entities();
    this->_texture_container.unload_all_textures();
    this->_image_container.unload_all_images();
    this->_font_container.unload_all_fonts();

    // By this point, all components should be already destroyed

    this->_graphics_component_manager.exit();
    this->_behavior_component_manager.exit();
    this->_physics_component_manager.exit();
    this->_game_manager.exit();
}

