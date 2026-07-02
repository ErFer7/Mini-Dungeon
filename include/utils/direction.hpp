#pragma once

#include <cstdint>
#include <random>

namespace utils {

enum class Direction : uint8_t {
    NONE = 0b0000,
    TOP = 0b1000,
    BOTTOM = 0b0100,
    LEFT = 0b0010,
    RIGHT = 0b0001,
    CENTER = NONE,
    BOTTOM_LEFT = BOTTOM | LEFT,
    BOTTOM_RIGHT = BOTTOM | RIGHT,
    TOP_LEFT = TOP | LEFT,
    TOP_RIGHT = TOP | RIGHT,
    HORIZONTAL = LEFT | RIGHT,
    BOTTOM_HORIZONTAL = BOTTOM | HORIZONTAL,
    TOP_HORIZONTAL = TOP | HORIZONTAL,
    VERTICAL = TOP | BOTTOM,
    VERTICAL_LEFT = LEFT | VERTICAL,
    VERTICAL_RIGHT = RIGHT | VERTICAL,
    ALL = VERTICAL | HORIZONTAL
};

enum DirectionIndex : unsigned int { TOP = 0, BOTTOM = 1, LEFT = 2, RIGHT = 3, NONE = 4 };

inline DirectionIndex index(const Direction &direction) {
    switch (direction) {
        case Direction::TOP:
            return DirectionIndex::TOP;
        case Direction::BOTTOM:
            return DirectionIndex::BOTTOM;
        case Direction::LEFT:
            return DirectionIndex::LEFT;
        case Direction::RIGHT:
            return DirectionIndex::RIGHT;
        default:
            return DirectionIndex::NONE;
    }
}

inline DirectionIndex direct_opposite(const DirectionIndex &direction_index) {
    switch (direction_index) {
        case DirectionIndex::TOP:
            return DirectionIndex::BOTTOM;
        case DirectionIndex::BOTTOM:
            return DirectionIndex::TOP;
        case DirectionIndex::LEFT:
            return DirectionIndex::RIGHT;
        case DirectionIndex::RIGHT:
            return DirectionIndex::LEFT;
        default:
            return DirectionIndex::NONE;
    }
}

inline Direction operator|(Direction a, Direction b) {
    return static_cast<Direction>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline Direction operator|=(Direction &a, Direction b) {
    uint8_t temp_a = static_cast<uint8_t>(a) | static_cast<uint8_t>(b);
    a = static_cast<Direction>(temp_a);

    return a;
}

inline Direction operator&(Direction a, Direction b) {
    return static_cast<Direction>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline Direction operator&=(Direction &a, Direction b) {
    uint8_t temp_a = static_cast<uint8_t>(a) & static_cast<uint8_t>(b);
    a = static_cast<Direction>(temp_a);

    return a;
}

inline Direction operator~(Direction a) { return static_cast<Direction>(~static_cast<uint8_t>(a) & 0b1111); }

inline Direction opposite(Direction direction) {
    return static_cast<Direction>(~static_cast<uint8_t>(direction) & 0b1111);
}

inline Direction random_direction(std::mt19937 &generator) {
    // In order to avoid rebuild this object at every call, we will make it global
    static std::uniform_int_distribution<uint8_t> distribution(0, 4);

    // The shift of 4 will lead to 0b10000, which will become 0 (CENTER or NONE)
    return static_cast<Direction>((1 << distribution(generator)) & 0b1111);
}

inline Direction random_directions(std::mt19937 &generator) {
    // In order to avoid rebuild this object at every call, we will make it global
    static std::uniform_int_distribution<uint8_t> distribution(0, 15);

    return static_cast<Direction>(distribution(generator));
}

inline unsigned int direction_count(Direction direction) {
    unsigned int count = 0;

    for (unsigned int i = 0; i < 4; i++) {
        count += (static_cast<unsigned int>(direction) >> i) & 1;
    }

    return count;
}

}  // namespace utils
