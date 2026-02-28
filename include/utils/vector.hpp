#pragma once

#include <raylib.h>

#include <cmath>
#include <concepts>
#include <sstream>
#include <string>

#include "definitions.hpp"

namespace utils {

template <typename T>
concept Numeric = std::same_as<T, float> || std::same_as<T, double> || std::same_as<T, int>;

template <Numeric T = float>
struct Vector2D {
    Vector2D() : x(0), y(0) {}

    Vector2D(T x, T y) : x(x), y(y) {}

    Vector2D(const Vector2D &other) {
        if (this == &other) {
            return;
        }

        x = other.x;
        y = other.y;
    }

    Vector2D(Vector2 &&other) noexcept {
        if (this == &other) {
            return;
        }

        x = std::move(other.x);
        y = std::move(other.y);
    }

    explicit Vector2D(T value) : x(value), y(value) {}

    template <Numeric U>
    explicit Vector2D(const Vector2D<U> &other) : x(static_cast<T>(other.x)),
                                                  y(static_cast<T>(other.y)) {}

    explicit Vector2D(const Vector2 &raylib_vector)
        : x(static_cast<T>(raylib_vector.x)),
          y(static_cast<T>(raylib_vector.y)) {}

    template <Numeric U>
    explicit operator Vector2D<U>() const {
        return Vector2D<U>(static_cast<U>(x), static_cast<U>(y));
    }

    operator Vector2() const { return Vector2{static_cast<float>(x), static_cast<float>(y)}; }

    operator std::string() const {
        std::ostringstream string;
        string << '{' << x << ", " << y << '}';

        return string.str();
    }

    Vector2D &operator=(const Vector2D &other) {
        if (this == &other) {
            return *this;
        }

        x = other.x;
        y = other.y;

        return *this;
    }

    Vector2D &operator=(Vector2D &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        x = std::move(other.x);
        y = std::move(other.y);

        return *this;
    }

    Vector2D operator+(const Vector2D &other) const { return Vector2D(x + other.x, y + other.y); }

    Vector2D &operator+=(const Vector2D &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D operator-(const Vector2D &other) const { return Vector2D(x - other.x, y - other.y); }

    Vector2D &operator-=(const Vector2D &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2D operator*(T scalar) const { return Vector2D(x * scalar, y * scalar); }

    Vector2D &operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D operator*(const Vector2D &other) const { return Vector2D(x * other.x, y * other.y); }

    Vector2D &operator*=(const Vector2D &other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2D operator/(T scalar) const { return Vector2D(x / scalar, y / scalar); }

    Vector2D &operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2D operator/(const Vector2D &other) const { return Vector2D(x / other.x, y / other.y); }

    Vector2D &operator/=(const Vector2D &other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2D operator-() const { return Vector2D(-x, -y); }

    bool operator==(const Vector2D &other) const { return x == other.x && y == other.y; }

    bool operator!=(const Vector2D &other) const { return !(*this == other); }

    bool is_zero() const { return x == 0 && y == 0; }

    bool is_approximately_zero() const { return approximately_equal(*this, Vector2D<T>()); }

    T dot(const Vector2D &other) const { return x * other.x + y * other.y; }

    T cross(const Vector2D &other) const { return x * other.y - y * other.x; }

    T magnitude() const { return std::sqrt(x * x + y * y); }

    // This is useful for calculating the Manhattan distance
    T square_magnitude() const { return x * x + y * y; }

    Vector2D normalized() const {
        T magnitude_ = magnitude();

        if (magnitude_ == 0) {
            return Vector2D(0, 0);
        }

        return Vector2D(x / magnitude_, y / magnitude_);
    }

    void normalize() {
        T magnitude_ = magnitude();

        if (magnitude_ != 0) {
            x /= magnitude_;
            y /= magnitude_;
        }
    }

    T distance(const Vector2D &other) const { return (*this - other).magnitude(); }

    T square_distance(const Vector2D &other) const { return (*this - other).square_magnitude(); }

    Vector2D lerp(const Vector2D &other, T t) const { return Vector2D(x + t * (other.x - x), y + t * (other.y - y)); }

    // Rotated 90 degrees counter-clockwise
    Vector2D perpendicular() const { return Vector2D(-y, x); }

    T angle() const { return std::atan2(y, x); }

    T angle_to(const Vector2D &other) const { return std::atan2(cross(other), dot(other)); }

    Vector2D rotated(float angle) const {
        T cos = std::cos(angle);
        T sin = std::sin(angle);

        return Vector2D(x * cos - y * sin, x * sin + y * cos);
    }

    Vector2D rotated(Vector2D origin, float angle) const {
        Vector2D vector = this - origin;

        vector.rotate(origin, angle);

        return vector;
    }

    void rotate(float angle) {
        T cos = std::cos(angle);
        T sin = std::sin(angle);

        x = x * cos - y * sin;
        y = x * sin + y * cos;
    }

    void rotate(Vector2D origin, float angle) {
        *this -= origin;

        T cos = std::cos(angle);
        T sin = std::sin(angle);

        x = x * cos - y * sin;
        y = x * sin + y * cos;

        *this += origin;
    }

    T x;
    T y;
};

typedef Vector2D<int> Vector2Di;
typedef Vector2D<float> Vector2Df;
typedef Vector2D<double> Vector2Dd;

template <Numeric T>
Vector2D<T> operator*(T scalar, const Vector2D<T> &vector) {
    return vector * scalar;
}

template <Numeric T>
std::ostream &operator<<(std::ostream &os, const Vector2D<T> &vector) {
    os << "Vector2D { x: " << vector.x << ", y: " << vector.y << '}';
    return os;
}

template <Numeric T>
bool approximately_equal(const Vector2D<T> &vector_a, const Vector2D<T> &vector_b) {
    if constexpr (std::same_as<T, float>) {
        return std::abs(vector_a.x - vector_b.x) < FLOAT_EPSILON && std::abs(vector_a.y - vector_b.y) < FLOAT_EPSILON;
    }

    if constexpr (std::same_as<T, double>) {
        return std::abs(vector_a.x - vector_b.x) < DOUBLE_EPSILON && std::abs(vector_a.y - vector_b.y) < DOUBLE_EPSILON;
    }

    return vector_a.x == vector_b.x && vector_a.y == vector_b.y;
}

}  // namespace utils
