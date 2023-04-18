#pragma once

#include "IService.hpp"

/**
 * @brief The InputManager class that manages the input of the game
 *
 */
class InputManager : public IService {
    friend class ServiceLocator;

   public:
    /**
     * @brief Shutdown the InputManager
     *
     */
    void ShutDown() override;

    /**
     * @brief Update the input state
     *
     */
    void Update() override;

    struct InputState {
        bool quit = false;
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
    };

    /**
     * @brief Input state of this frame
     * @details Updated in Update()
     */
    InputState m_inputStateThisFrame;

   private:
    static InputManager &instance();
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) = delete;
};