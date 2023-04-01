#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include "Component.hpp"

// Directions of movement
const int8_t DIR_LEFT = -1;
const int8_t DIR_RIGHT = 1;
const int8_t DIR_UP = -1;
const int8_t DIR_DOWN = 1;
const int8_t DIR_STAND = 0;

class ControllerComponent : public Component
{
public:
    // Constructor
    ControllerComponent();
    // Destructor
    ~ControllerComponent();
    // Analyze input from player, update the direction
    void Update() override;
    // Getter of movement direction
    int8_t GetDirectionX();
    int8_t GetDirectionY();
    bool QuitProgram();

private:
    int8_t m_direction_x;
    int8_t m_direction_y;
    // record key state, 0 -> Key 'a' or 'left', 1 -> Key 'd' or 'right'
    bool m_buttons[4] = {};
    bool m_quit = false;
};

#endif
