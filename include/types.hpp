#pragma once

#include <concepts>
#include <cstdint>
#include <memory>

// TODO: Clean this file

// Core
class GameCore;

// Utilities
namespace utils {

class ActivityState;
enum class Direction : uint8_t;

template <typename... Args>
class Event;

class Listener;

class Transform;
class TransformData;
class Uncopiable;

template <typename T>
concept Numeric = std::same_as<T, float> || std::same_as<T, double> || std::same_as<T, int>;

template <Numeric T = float>
struct Vector2D;

class IdReferences;
class Identified;

template <typename Type>
class Handle;

}  // namespace utils

class Quadtree;

// Components
class Component;

class AudioComponent;

class BehaviorComponent;

class ButtonComponent;
class ButtonClickEvent;
class ButtonClickListener;

class DoorComponent;
struct DoorComponentArgs;

class PlayerComponent;

class ColliderComponent;
class CollisionEvent;
class CollisionListener;
struct ColliderComponentArgs;

class GraphicsComponent;
struct GraphicsComponentArgs;

class PhysicsComponent;
struct PhysicsComponentArgs;

class TextComponent;
struct TextComponentArgs;

class TransformComponent;
class TransformUpdateEvent;
class TransformUpdateListener;
struct TransformComponentArgs;

class UITransformComponent;
struct UITransformComponentArgs;

// Containers
template <typename DataStructure, typename LocalIdentifier, typename Object>
class Container;

template <typename T>
struct IsUniquePtr : std::false_type {};
template <typename T, typename D>
struct IsUniquePtr<std::unique_ptr<T, D>> : std::true_type {};

template <typename T>
concept IdentifiedCompatible =
    std::derived_from<T, utils::Identified> ||
    (IsUniquePtr<T>::value && std::derived_from<typename T::element_type, utils::Identified>);

template <typename Object>
    requires IdentifiedCompatible<Object>
class VectorContainer;

template <typename LocalIdentifier, typename Object>
class MapContainer;

class FontContainer;
class ImageContainer;
class TextureContianer;

template <typename ComponentType>
class StackAllocatedComponentContainer;

class PhysicsComponentContainer;
class ColliderComponentContainer;
class TransformComponentContainer;

class HeapAllocatedComponentContainer;
class BehaviorComponentContainer;

class EntityContainer;

// Entities
class Entity;
class ComponentsMap;

class Entity2D;
struct Entity2DArgs;

class StaticPhysicalEntity2D;
struct StaticPhysicalEntity2DArgs;

class DynamicPhysicalEntity2D;
struct DynamicPhysicalEntity2DArgs;

class Door;
struct DoorArgs;

class Player;

class Sword;

class UIEntity;
struct UIEntityArgs;

class Background;

class Button;
struct ButtonArgs;

class Text;
struct TextArgs;

class TextButton;
struct TextButtonArgs;

// Gameplay
class Dungeon;
class Room;
struct DoorMap;

// Managers
class Manager;

class GraphicalDebuggingManager;

enum class RenderingMode;
enum class SortingMode;

class GraphicsManager;
class ScreenResizeEvent;
class ScreenResizeListener;

class Space;
class GraphicsComponentVector;

class AudioManager;

class BehaviorManager;
class BehaviorComponentVector;

class GameManager;

class PhysicsManager;

// Scenes
class Scene;
class MenuScene;
class GameplayScene;
