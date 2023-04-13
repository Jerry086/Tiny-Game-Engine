#ifndef CONTROLLERCOMPONENT_HPP
#define CONTROLLERCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <cstdint>
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
    /**
     * Constructor
     */
    ControllerComponent();
    /**
     * Destructor
     */
    ~ControllerComponent();
    /**
     * Update game object's moving direction based on user input.
     */
    void Update() override;
    /**
     * Getter of current moving direction towards x-axis
     */
    int8_t GetDirectionX();
    /**
     * Getter of current moving direction towards y-axis
     */
    int8_t GetDirectionY();
    /**
     * Getter of quit flag
     */
    bool QuitProgram();

private:
    int8_t m_direction_x = DIR_RIGHT;
    int8_t m_direction_y = DIR_STAND;
    bool m_quit = false;
};

#endif
