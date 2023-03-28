#ifndef BALL_HPP
#define BALL_HPP
#include <iostream>
#include "Vec.hpp"
#include "constants.hpp"
 
class Ball
{
public:
	Ball(Vec2 position, Vec2 velocity)
		: position(position), velocity(velocity)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = BALL_WIDTH;
		rect.h = BALL_HEIGHT;
	}

	void Update(float dt);

	void Draw(/*SDL_Renderer *renderer*/);
	SDL_Rect getRect();
	void CollideWithPaddle(Contact const &contact);

	void CollideWithWall(Contact const &contact);

	Vec2 position;
	Vec2 velocity;
	SDL_Rect rect{};
};
#endif