#ifndef GAMEOBJECTMANAGER
#define GAMEOBJECTMANAGER

#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "./Components/SpriteComponent.hpp"
#include "./Services/ResourceManager.hpp"
#include "GameObject.hpp"

#define GameOver "./sprites/gameOver.bmp"

/**
 * @brief The GameObjectManager class
 *
 * Singleton class that manages all game objects
 */
class GameObjectManager {
   public:
    /**
     * @brief instance of the game object manager
     */
    static GameObjectManager &instance();
    /**
     * @brief start up the game object manager
     */
    void StartUp();
    /**
     * @brief shut down the game object manager
     */
    void ShutDown();
    /**
     * @brief update all game objects of the game
     */
    void Update();
    /**
     * @brief render all game objects of the game
     */
    void Render();
    /**
     * @brief add a game object to the game object manager
     * @param objectID The id of the game object
     * @param go The game object to add
     */
    void AddGameObject(std::string objectID, std::shared_ptr<GameObject> go);
    /**
     * @brief remove a game object from the game object manager
     * @param objectID The id of the game object
     */
    void RemoveGameObject(std::string objectID);
    /**
     * @brief get a game object from the game object manager
     * @param objectID The id of the game object
     * @return The game object
     */
    std::shared_ptr<GameObject> GetGameObject(std::string objectID);
    /**
     * @brief set the game over flag
     * @param shutdown The game over flag
     */
    void SetGameOver(bool gameOver);

    std::map<std::string, std::shared_ptr<GameObject>> m_gameobjects;

   private:
    bool m_gameOver = false;
    std::shared_ptr<SpriteComponent> m_sprite;
    GameObjectManager();
    ~GameObjectManager();
    GameObjectManager(const GameObjectManager &) = delete;
    GameObjectManager &operator=(const GameObjectManager &) = delete;
};

#endif
