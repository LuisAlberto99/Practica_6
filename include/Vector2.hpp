#pragma once

struct Vector2
{
    float x{0.0f};
    float y{0.0f};

    constexpr Vector2() = default;
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &other) const
    {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2 &other) const
    {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(float scalar) const
    {
        return {x * scalar, y * scalar};
    }

    float length_squared() const
    {
        return x * x + y * y;
    }

    float length() const;
    Vector2 normalized() const;
    Vector2 clamp(const Vector2 &min, const Vector2 &max) const;
};