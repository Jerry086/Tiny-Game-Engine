#include "ControllerComponent.hpp"

ControllerComponent::ControllerComponent(bool *quit) : m_quit(quit) {}

ControllerComponent::~ControllerComponent() {}

// Update game object's moving direction based on user input.
// Flip 'quit' to true upon quit event
void ControllerComponent::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // quit the program
        if (event.type == SDL_QUIT)
        {
            *m_quit = true;
        }
        // Record key state (up/down)
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
            {
                m_buttons[0] = true;
            }
            else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
            {
                m_buttons[1] = true;
            }
            else if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
            {
                m_buttons[2] = true;
            }
            else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
            {
                m_buttons[3] = true;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
            {
                m_buttons[0] = false;
            }
            else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
            {
                m_buttons[1] = false;
            }
            else if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
            {
                m_buttons[2] = false;
            }
            else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
            {
                m_buttons[3] = false;
            }
        }
    }
    // Translate key state to moving direction
    if (m_buttons[0])
    {
        m_direction_x = DIR_LEFT;
    }
    else if (m_buttons[1])
    {
        m_direction_x = DIR_RIGHT;
    }
    else if (m_buttons[2])
    {
        m_direction_y = DIR_UP;
    }
    else if (m_buttons[3])
    {
        m_direction_y = DIR_DOWN;
    }
    else
    {
        m_direction_x = DIR_STAND;
        m_direction_y = DIR_STAND;
    }
}

// Getter of current moving direction
int8_t ControllerComponent::GetDirectionX()
{
    return m_direction.x;
}

int8_t ControllerComponent::GetDirectionY()
{
    return m_direction.y;
}
