#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include <cstdint>
#include "Component.hpp"

// Directions of movement
const int DIR_LEFT = -1;
const int DIR_RIGHT = 1;
const int DIR_UP = -1;
const int DIR_DOWN = 1;
const int DIR_STAND = 0;

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
    int GetDirectionX();
    int GetDirectionY();
    bool QuitProgram();

private:
    int m_direction_x = 0;
    int m_direction_y = 0;
    // record key state, 0 -> Key 'a' or 'left', 1 -> Key 'd' or 'right'
    bool m_buttons[4] = {};
    bool m_quit = false;
};

#endif
