#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace py = pybind11;

#include "./Components/Component.hpp"

/**
 * @brief The GameObject class
 *
 * The GameObject class is the base class for all game objects.
 *
 */
class GameObject {
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

    /**
     * @brief Get a list of components of a given type
     *
     * @tparam T The type of the component
     * @return std::vector<std::shared_ptr<T>> A vector of components
     */
    // For some pybind reason it can only be implemented in header
    template <typename T>
    std::vector<std::shared_ptr<T>> GetComponents() {
        std::vector<std::shared_ptr<T>> components;
        for (auto it = m_components.begin(); it != m_components.end(); it++) {
            std::shared_ptr<T> component =
                std::dynamic_pointer_cast<T>(it->second);
            if (component != nullptr) {
                components.push_back(component);
            }
        }
        return components;
    }

    /**
     * @brief Get a list of components of a given type
     *
     * @tparam T The type of the component
     * @return pybind11::list A pybind list of components
     */
    // For some pybind reason it can only be implemented in header
    template <typename T>
    pybind11::list GetComponentsPython() {
        std::vector<std::shared_ptr<T>> components = GetComponents<T>();
        pybind11::list result;
        for (auto it = components.begin(); it != components.end(); it++) {
            result.append(*it);
        }
        return result;
    }

   private:
    std::string gameObject_id;
    std::map<std::string, std::shared_ptr<Component>> m_components;
    std::shared_ptr<Component> m_collisionComponent = nullptr;
};

#endif
