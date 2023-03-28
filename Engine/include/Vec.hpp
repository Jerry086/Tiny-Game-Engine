#ifndef Vec2_HPP
#define Vec2_HPP

class Vec2
{
public:
	Vec2()
		: x(0.0f), y(0.0f)
	{
	}

	Vec2(float x, float y)
		: x(x), y(y)
	{
	}

	Vec2 operator+(Vec2 const &rhs);

	Vec2 &operator+=(Vec2 const &rhs);

	Vec2 operator*(float rhs);

	float x, y;
};

#endif