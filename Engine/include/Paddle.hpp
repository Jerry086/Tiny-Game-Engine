#ifndef PADDLE_HPP
#define PADDLE_HPP
#include "Vec.hpp"

#include "constants.hpp"

class Paddle
{
public:
	Paddle(Vec2 position, Vec2 velocity)
		: position(position), velocity(velocity)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = PADDLE_WIDTH;
		rect.h = PADDLE_HEIGHT;
	}

	void Update(float dt);

	void Draw(/*SDL_Renderer *renderer*/);
SDL_Rect getRect();
	Vec2 position;
	Vec2 velocity;
	SDL_Rect rect{};
};
#endif