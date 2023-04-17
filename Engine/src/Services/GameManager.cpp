#include "./Services/GameManager.hpp"

#include "./Services/InputManager.hpp"
#include "./Services/SDLWrapper.hpp"
#include "./Services/ServiceLocator.hpp"
#include "SDLGraphicsProgram.h"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

GameManager& GameManager::instance() {
    static GameManager instance;
    return instance;
}

void GameManager::ShutDown() {}

void GameManager::StartUp() { m_isQuit = false; }

void GameManager::Update() {
    m_isQuit =
        ServiceLocator::GetService<InputManager>().m_inputStateThisFrame.quit;
}

bool GameManager::IsQuit() { return GameManager::instance().m_isQuit; }
