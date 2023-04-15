#include "./Services/GameManager.hpp"

#include "./Services/InputService.hpp"
#include "./Services/ServiceLocator.hpp"

GameManager &GameManager::instance() {
    static GameManager instance;
    return instance;
}

void GameManager::ShutDown() {}

void GameManager::Update() {
    m_isQuit = InputService::instance().m_inputStateThisFrame.quit;
}

bool GameManager::IsQuit() { return GameManager::instance().m_isQuit; }
