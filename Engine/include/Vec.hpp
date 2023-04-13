#ifndef Vec2_HPP
#define Vec2_HPP

/**
 * A 2D vector class
 */
class Vec2
{
public:
	/**
	 * Default constructor
	 */
	Vec2() : x(0.0f), y(0.0f) {}
	/**
	 * Constructor
	 * @param x The x coordinate
	 * @param y The y coordinate
	 */
	Vec2(float x, float y) : x(x), y(y) {}
	/**
	 * Overloaded + operator
	 * @param rhs The right hand side of the operator
	 */
	Vec2 operator+(Vec2 const &rhs);
	/**
	 * Overloaded += operator
	 * @param rhs The right hand side of the operator
	 */
	Vec2 &operator+=(Vec2 const &rhs);
	/**
	 * Overloaded * operator
	 * @param rhs The right hand side of the operator
	 */
	Vec2 operator*(float rhs);

	float x, y;
};

#endif