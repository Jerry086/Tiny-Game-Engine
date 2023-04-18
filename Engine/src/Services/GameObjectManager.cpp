#include "./Services/GameObjectManager.hpp"

#include <pybind11/embed.h>

#include <iterator>

#include "./Components/CollisionComponent.hpp"
#include "./Components/SpriteComponent.hpp"
#include "./Services/ResourceManager.hpp"
#include "GameObject.hpp"

namespace py = pybind11;

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
    // import script directory
    auto sys = py::module_::import("sys");
    auto path = sys.attr("path");
    path.attr("insert")(0, "./Assets/scripts");

    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
        it->second->StartUp();
    }
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
}
/**
 * Update all game objects of the game.
 * The order of the update is not important.
 */
void GameObjectManager::Update()
{
    for (auto it = m_gameobjects.begin(); it != m_gameobjects.end(); it++)
    {
        if (!it->second->m_enabled)
        {
            continue;
        }
        it->second->Update();
    }
}
/**
 * Render all game objects of the game
 */
void GameObjectManager::Render()
{
    // renders none first
    for (auto it = m_gameobjects.rbegin(); it != m_gameobjects.rend(); it++)
    {
        if (!it->second->m_enabled)
        {
            continue;
        }

        if (it->second->GetComponents<CollisionComponent>().empty() ||
            it->second->GetComponents<CollisionComponent>()[0]
                    ->GetObjectType() != ObjectType::none)
        {
            continue;
        }
        it->second->Render();
    }

    // then wall
    for (auto it = m_gameobjects.rbegin(); it != m_gameobjects.rend(); it++)
    {
        if (!it->second->m_enabled)
        {
            continue;
        }

        // renders none first
        if (it->second->GetComponents<CollisionComponent>().empty() ||
            it->second->GetComponents<CollisionComponent>()[0]
                    ->GetObjectType() != ObjectType::wall)
        {
            continue;
        }
        it->second->Render();
    }

    // then active objects
    for (auto it = m_gameobjects.rbegin(); it != m_gameobjects.rend(); it++)
    {
        if (!it->second->m_enabled)
        {
            continue;
        }

        // renders none first
        if (it->second->GetComponents<CollisionComponent>().empty() ||
            it->second->GetComponents<CollisionComponent>()[0]
                    ->GetObjectType() == ObjectType::wall ||
            it->second->GetComponents<CollisionComponent>()[0]
                    ->GetObjectType() == ObjectType::none)
        {
            continue;
        }
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
void GameObjectManager::SetGameOver(bool gameOver) { m_gameOver = gameOver; }
