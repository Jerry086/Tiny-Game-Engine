#ifndef CONSTANT_H
#define CONSTANT_H
#include <SDL2/SDL.h>
 
enum CollisionType
{
    None,
    Top,
    Middle,
    Bottom,
    Left,
    Right
};

enum Buttons
{
    PaddleOneUp = 0,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};

class Contact
{
public:
    Contact(){};
    int type = 0;
    float penetration =0;
};

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float BALL_SPEED = 1.0f;
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

const float PADDLE_SPEED = 1.0f;
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;
#endif