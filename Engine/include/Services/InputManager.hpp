#pragma once

#include "IService.hpp"

class InputManager : public IService {
    friend class ServiceLocator;

   public:
    void ShutDown() override;
    void Update() override;

    struct InputState {
        bool quit = false;
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
    };

    InputState m_inputStateThisFrame;

   private:
    static InputManager &instance();
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) = delete;
};