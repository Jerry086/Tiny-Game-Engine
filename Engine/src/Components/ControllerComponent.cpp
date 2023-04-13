#include "./Components/ControllerComponent.hpp"
/**
 * Constructor
 */
ControllerComponent::ControllerComponent() {}
/**
 * Destructor
 */
ControllerComponent::~ControllerComponent() {}
/**
 * Update game object's moving direction based on user input.
 * Flip 'm_quit' to true upon quit event
 */
void ControllerComponent::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_quit = true;
        }
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
/**
 * Getter of current moving direction towards x-axis
 */
int8_t ControllerComponent::GetDirectionX()
{
    return m_direction_x;
}
/**
 * Getter of current moving direction towards y-axis
 */
int8_t ControllerComponent::GetDirectionY()
{
    return m_direction_y;
}
/**
 * Getter of the component type
 */
int ControllerComponent::GetType()
{
    return m_type;
}
/**
 * Getter of quit flag
 */
bool ControllerComponent::QuitProgram()
{
    return m_quit;
}
