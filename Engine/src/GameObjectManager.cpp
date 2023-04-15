#include "GameObjectManager.hpp"

#include <iterator>

/**
 * Private constructor
 */
GameObjectManager::GameObjectManager() {}
/**
 * Private destructor
 */
GameObjectManager::~GameObjectManager() {}
/**
 * Obtain the instance of the game object manager
 */
GameObjectManager &GameObjectManager::instance()
{
    static GameObjectManager instance;
    return instance;
}
/**
 * Start up the game object manager
 */
void GameObjectManager::StartUp()
{
    std::shared_ptr<TransformComponent> transform =
        std::make_shared<TransformComponent>(Vec2(0, 0));
    m_sprite = std::make_shared<SpriteComponent>(GameOver, transform, 0, 0, 1400, 815, 1, 1, 1);
}
/**
 * Shut down the game object manager by shutting down all game objects
 * and removing them from the game object manager
 */
void GameObjectManager::ShutDown()
{
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
        it->second->ShutDown();
    }
    m_gameobjects.clear();
    m_sprite->ShutDown();
}
/**
 * Update all game objects of the game.
 * The order of the update is not important.
 */
void GameObjectManager::Update()
{
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
        it->second->Update();
    }
}
/**
 * Render all game objects of the game
 * The order of the render is not important.
 */
void GameObjectManager::Render()
{
    if (m_gameOver)
    {
        m_sprite->Render();
        return;
    }
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
        it->second->Render();
    }
}
/**
 * Add a game object to the game object manager. The objectID must
 * be unique.
 */
void GameObjectManager::AddGameObject(std::string objectID,
                                      std::shared_ptr<GameObject> go)
{
    m_gameobjects.emplace(objectID, go);
}
/**
 * Remove a game object from the game object manager by its objectID
 */
void GameObjectManager::RemoveGameObject(std::string objectID)
{
    m_gameobjects.erase(objectID);
}
/**
 * Get a game object from the game object manager by its objectID
 */
std::shared_ptr<GameObject> GameObjectManager::GetGameObject(
    std::string objectID)
{
    return m_gameobjects[objectID];
}
/**
 * Set the shutdown flag when game is over
 */
void GameObjectManager::SetGameOver(bool gameOver)
{
    m_gameOver = gameOver;
}
