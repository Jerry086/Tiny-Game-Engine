#ifndef GAMEOBJECTMANAGER
#define GAMEOBJECTMANAGER

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <map>

#include "GameObject.hpp"
// #include "./Components/CollisionComponent.hpp"

/**
 * This class sets up the main game engine
 */
class GameObjectManager
{
public:
    static GameObjectManager &instance();
    GameObjectManager();
    ~GameObjectManager();
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
};

#endif
