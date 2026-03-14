#pragma once

#include <concepts>
#include <memory>

// TODO: Clean this file

class GameCore;

namespace utils {

class ActivityState;
class IdReferences;
class Identified;
template <typename Type>
class Handle;

}  // namespace utils

template <typename T>
struct IsUniquePtr : std::false_type {};
template <typename T, typename D>
struct IsUniquePtr<std::unique_ptr<T, D>> : std::true_type {};

template <typename T>
concept IdentifiedCompatible =
    std::derived_from<T, utils::Identified> ||
    (IsUniquePtr<T>::value && std::derived_from<typename T::element_type, utils::Identified>);

// Components
class Component;

class AudioComponent;

class BehaviorComponent;

class ButtonComponent;
class ButtonClickEvent;
class ButtonClickListener;

class PlayerComponent;

class GraphicsComponent;
struct GraphicsComponentArgs;

class PhysicsComponent;
struct PhysicsComponentArgs;

class ColliderComponentContainer;

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
template <typename DataStructure, typename LocalIdentifier, typename Object>
class Container;

template <typename Object>
    requires IdentifiedCompatible<Object>
class VectorContainer;

class PhysicsComponentContainer;
class TransformComponentContainer;
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

class StaticPhysicalEntity2D;

class Player;
typedef StaticPhysicalEntity2D Wall;
class Background;
class Text;
class TextButton;

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

class BehaviorManager;

class GraphicsManager;
enum class RenderingMode;
class Space;

class GraphicalDebuggingManager;

class MainBehaviourManager;

// Scenes
class Scene;
class MenuScene;
class GameplayScene;

class Dungeon;
class Room;

// Enums
enum class SortingMode;

// structs
struct Layer;

// Utilities are not included here
