#include "Vector2.hpp"
#include <cmath>

float Vector2::length()const
{
    return std::sqrt(length_squared());
}

Vector2 Vector2::normalized() const
{
    float len = length();
    if (len > 0.0001f)
    {
        return {x / len, y / len};
    }
    return {0.0f, 0.0f};
}

Vector2 Vector2::clamp(const Vector2 &min, const Vector2 &max) const
{
    Vector2 result;
    result.x = x < min.x ? min.x : (x > max.x ? max.x : x);
    result.y = y < min.y ? min.y : (y > max.y ? max.y : y);
    return result;
}
