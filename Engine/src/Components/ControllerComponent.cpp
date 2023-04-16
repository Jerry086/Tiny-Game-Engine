#include "./Components/ControllerComponent.hpp"

#include "./Services/InputManager.hpp"
#include "./Services/ServiceLocator.hpp"
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
void ControllerComponent::Update() {
    InputManager::InputState state =
        ServiceLocator::GetService<InputManager>().m_inputStateThisFrame;
    if (state.left) {
                m_buttons[1] = false;
                m_buttons[2] = false;
                m_buttons[3] = false;
                m_buttons[0] = false;
                m_buttons[2] = false;
                m_buttons[3] = false;
                m_buttons[0] = false;
                m_buttons[1] = false;
                m_buttons[3] = false;
        // we do not need to record key up state for pacman
        // else if (event.type == SDL_KEYUP)
        // {
        //     if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
        //     {
        //         m_buttons[0] = false;
        //     }
        //     else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
        //     {
        //         m_buttons[1] = false;
        //     }
        //     else if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
        //     {
        //         m_buttons[2] = false;
        //     }
        //     else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
        //     {
        //         m_buttons[3] = false;
        //     }
        // }
        m_direction_x = DIR_LEFT;
        m_direction_y = DIR_STAND;
    } else if (state.right) {
        m_direction_x = DIR_RIGHT;
        m_direction_y = DIR_STAND;
    } else if (state.up) {
        m_direction_x = DIR_STAND;
        m_direction_y = DIR_UP;
    } else if (state.down) {
        m_direction_x = DIR_STAND;
        m_direction_y = DIR_DOWN;
    }
}
/**
 * Getter of current moving direction towards x-axis
 */
int8_t ControllerComponent::GetDirectionX() { return m_direction_x; }
/**
 * Getter of current moving direction towards y-axis
 */
int8_t ControllerComponent::GetDirectionY() { return m_direction_y; }
/**
 * Getter of the component type
 */
int ControllerComponent::GetType() { return m_type; }
/**
 * Getter of quit flag
 */
bool ControllerComponent::QuitProgram() { return m_quit; }
