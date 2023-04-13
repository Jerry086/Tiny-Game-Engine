#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <map>
#include <memory>
#include <string>

#include "./Components/Component.hpp"

/**
 * @brief The GameObject class
 *
 * The GameObject class is the base class for all game objects.
 *
 */
class GameObject
{
public:
    /**
     * @brief Constructor
     * @param id The id of the game object
     */
    GameObject(std::string id);
    /**
     * @brief Destructor
     */
    ~GameObject();
    /**
     * @brief StartUp the game object
     */
    void StartUp();
    /**
     * @brief ShutDown the game object
     */
    void ShutDown();
    /**
     * @brief Update the game object
     */
    void Update();
    /**
     * @brief Render the game object
     */
    void Render();
    /**
     * @brief Add a component to the game object
     * @param componentName The id of the component
     * @param component The component to add
     */
    void AddComponent(std::string componentName,
                      std::shared_ptr<Component> component);
    /**
     * @brief Remove a component from the game object
     * @param componentName The id of the component to remove
     */
    void RemoveComponent(std::string componentName);
    /**
     * @brief Get a component from the game object
     * @param componentName The id of the component to get
     * @return The component
     */
    std::shared_ptr<Component> GetComponent(std::string componentName);

    std::map<std::string, std::shared_ptr<Component>> m_components;

private:
    std::string gameObject_id;
};

#endif
