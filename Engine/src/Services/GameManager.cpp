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

void GameManager::Update() {
    m_isQuit = InputManager::instance().m_inputStateThisFrame.quit;
}

bool GameManager::IsQuit() { return GameManager::instance().m_isQuit; }

bool GameManager::IsGameOver() { return GameManager::instance().m_isGameOver; }

void GameManager::ShowGameOverPopup() {
    SDL_Window* window = ServiceLocator::GetService<SDLWrapper>()
                             .m_SDLGraphicsProgram->getSDLWindow();
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Title", "Message",
                             NULL);
}
