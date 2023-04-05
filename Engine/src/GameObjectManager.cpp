#include "GameObjectManager.hpp"

#include <map>
#include <string>
#include <memory>
#include <iterator>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
GameObjectManager::GameObjectManager() {}

// Proper shutdown and destroy initialized objects
GameObjectManager::~GameObjectManager() {}

GameObjectManager &GameObjectManager::instance()
{
    static GameObjectManager instance;
    return instance;
}

// Update SDL
void GameObjectManager::Update()
{
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
        it->second->Update();
    }
}

void GameObjectManager::Render()
{
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
        it->second->Render();
    }
}

void GameObjectManager::AddGameObject(std::string objectID,
                                      std::shared_ptr<GameObject> go)
{
    m_gameobjects.emplace(objectID, go);
}

void GameObjectManager::RemoveGameObject(std::string objectID)
{
    m_gameobjects.erase(objectID);
}
