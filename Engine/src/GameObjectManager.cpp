#include "GameObjectManager.hpp"

#include <iterator>

GameObjectManager::GameObjectManager() {}

GameObjectManager::~GameObjectManager() {}

GameObjectManager &GameObjectManager::instance() {
    static GameObjectManager instance;
    return instance;
}

// Update SDL
void GameObjectManager::Update() {
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++) {
        it->second->Update();
    }
}

void GameObjectManager::Render() {
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++) {
        it->second->Render();
    }
}

void GameObjectManager::AddGameObject(std::string objectID,
                                      std::shared_ptr<GameObject> go) {
    m_gameobjects.emplace(objectID, go);
}

void GameObjectManager::RemoveGameObject(std::string objectID) {
    m_gameobjects.erase(objectID);
}

std::shared_ptr<GameObject> GameObjectManager::GetGameObject(
    std::string objectID) {
    return m_gameobjects[objectID];
}
