#include "./Services/InputService.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <cstdint>
#include <iostream>

InputService &InputService::instance() {
    static InputService instance;
    return instance;
}

void InputService::ShutDown() {}

void InputService::Update() {
    SDL_Event event;
    InputState state;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            state.quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_a ||
                event.key.keysym.sym == SDLK_LEFT) {
                state.left = true;
            } else if (event.key.keysym.sym == SDLK_d ||
                       event.key.keysym.sym == SDLK_RIGHT) {
                state.right = true;
            } else if (event.key.keysym.sym == SDLK_w ||
                       event.key.keysym.sym == SDLK_UP) {
                state.up = true;
            } else if (event.key.keysym.sym == SDLK_s ||
                       event.key.keysym.sym == SDLK_DOWN) {
                state.down = true;
            }
        }
    }
    m_inputStateThisFrame = state;
}