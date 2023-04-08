#ifndef GAMEOBJECTMANAGER
#define GAMEOBJECTMANAGER

#include <iostream>
#include <string>
#include <map>
#include <memory>

#include "GameObject.hpp"

/**
 * This class sets up the main game engine
 */
class GameObjectManager
{
public:
    static GameObjectManager &instance();
    void Update();
    void Render();

    void AddGameObject(std::string objectID, std::shared_ptr<GameObject> go);
    void RemoveGameObject(std::string objectID);

    // void Start();
    // void Shutdown();

    // std::map<std::string, std::shared_ptr<GameObject>> collision_objects;
    std::map<std::string, std::shared_ptr<GameObject>> m_gameobjects;

private:
    // std::map<std::string, std::shared_ptr<GameObject>> m_gameobjects;

    GameObjectManager();
    ~GameObjectManager();
    GameObjectManager(const GameObjectManager &) = delete;
    GameObjectManager &operator=(const GameObjectManager &) = delete;
};

#endif
