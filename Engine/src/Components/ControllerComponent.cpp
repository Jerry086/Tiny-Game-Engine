#include "./Components/ControllerComponent.hpp"

ControllerComponent::ControllerComponent() {}

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
            m_quit = true;
        }
        // handle keyboard input
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
            {
                m_direction_x = DIR_LEFT;
                m_direction_y = DIR_STAND;
            }
            else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
            {
                m_direction_x = DIR_RIGHT;
                m_direction_y = DIR_STAND;
            }
            else if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
            {
                m_direction_x = DIR_STAND;
                m_direction_y = DIR_UP;
            }
            else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
            {
                m_direction_x = DIR_STAND;
                m_direction_y = DIR_DOWN;
            }
        }
    }
}

// Getter of current moving direction
int8_t ControllerComponent::GetDirectionX()
{
    return m_direction_x;
}

int8_t ControllerComponent::GetDirectionY()
{
    return m_direction_y;
}

bool ControllerComponent::QuitProgram()
{
    return m_quit;
}
