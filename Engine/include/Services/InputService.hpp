#pragma once

#include "IService.hpp"

class InputService : public IService {
   public:
    static InputService &instance();
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
    InputService() = default;
    ~InputService() = default;
    InputService(const InputService &) = delete;
    InputService &operator=(const InputService &) = delete;
};