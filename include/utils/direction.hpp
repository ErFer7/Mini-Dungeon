#pragma once

#include <cstdint>
#include <random>

namespace utils {

enum class Direction : uint8_t {
    NONE = 0b0000,
    BOTTOM = 0b0100,
    LEFT = 0b0010,
    CENTER = NONE,
    RIGHT = 0b0001,
    TOP = 0b1000,
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

inline Direction operator|(Direction a, Direction b) {
    return a | b;
}

inline Direction operator|=(Direction a, Direction b) {
    a |= b;
    return a;
}

inline Direction operator&(Direction a, Direction b) {
    return a & b;
}

inline Direction operator&=(Direction a, Direction b) {
    a &= b;
    return a;
}

inline Direction operator~(Direction a) {
    return ~a;
}

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
