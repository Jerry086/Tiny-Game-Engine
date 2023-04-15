#include "./Services/GameManager.hpp"

#include "./Services/InputManager.hpp"
#include "./Services/ServiceLocator.hpp"

GameManager &GameManager::instance() {
    static GameManager instance;
    return instance;
}

void GameManager::ShutDown() {}

void GameManager::Update() {
    m_isQuit = InputManager::instance().m_inputStateThisFrame.quit;
}

bool GameManager::IsQuit() { return GameManager::instance().m_isQuit; }
