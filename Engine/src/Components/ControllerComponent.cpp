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
    else
    {
        m_direction_x = DIR_STAND;
    }

    if (m_buttons[2])
    {
        m_direction_y = DIR_UP;
    }
    else if (m_buttons[3])
    {
        m_direction_y = DIR_DOWN;
    }
    else
    {
        m_direction_y = DIR_STAND;
    }
    std::cout << "x: " << m_direction_x << " y: " << m_direction_y << std::endl;
}

// Getter of current moving direction
int ControllerComponent::GetDirectionX()
{
    return m_direction_x;
}

int ControllerComponent::GetDirectionY()
{
    return m_direction_y;
}

bool ControllerComponent::QuitProgram()
{
    return m_quit;
}
