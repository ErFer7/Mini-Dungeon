#pragma once

class GameCore;

// Components
class Component;

class AudioComponent;

class BehaviorComponent;

class ButtonComponent;
class ButtonClickEvent;
class ButtonClickListener;

class GraphicsComponent;
struct GraphicsComponentArgs;

class PhysicsComponent;
struct PhysicsComponentArgs;

class TextComponent;
struct TextComponentArgs;

class TransformComponent;
struct TransformComponentArgs;
class TransformUpdateEvent;
class TransformUpdateListener;

class UITransformComponent;
struct UITransformComponentArgs;
enum class UIOrigin;

// Containers
template <typename DataStructure, typename Identifier, typename Object>
class Container;

class PhysicsComponentContainer;
class AssetContainer;
class ImageMap;
class TextureMap;
class FontMap;

class EntityContainer;
class EntityVector;

// Entities
class Entity;
class ComponentsVector;

class Entity2D;
struct Entity2DArgs;

class UIEntity;
struct UIEntityArgs;

class Background;

class Button;
struct ButtonArgs;

class Text;
struct TextArgs;

class TextButton;
struct TextButtonArgs;

// Managers
class Manager;

template <typename ComponentType>
class ComponentManager;
class ComponentVector;

class AudioComponentManager;

class BehaviorComponentManager;

class GraphicsComponentManager;
enum class RenderingMode;

class MainBehaviourManager;

// Scenes
class Scene;
class MenuScene;

// Enums
enum class SortingMode;

// structs
struct Layer;
struct Space;

namespace utils {

class ActivityState;
class IdReferences;

}  // namespace utils

// Utilities are not included here
