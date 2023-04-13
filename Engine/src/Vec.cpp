#include "Vec.hpp"

/**
 * Overload the + operator for Vec2
 */
Vec2 Vec2::operator+(Vec2 const &rhs)
{

    return Vec2(x + rhs.x, y + rhs.y);
}
/**
 * Overload the += operator for Vec2
 */
Vec2 &Vec2::operator+=(Vec2 const &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}
/**
 * Overload the * operator for Vec2
 */
Vec2 Vec2::operator*(float rhs)
{
    return Vec2(x * rhs, y * rhs);
}