#include "GameObject.hpp"
/**
 * Constructor for the GameObject class
 * The id of the game object mush be unique
 */
GameObject::GameObject(std::string id) : gameObject_id(id) {}
/**
 * Destructor for the GameObject class
 */
GameObject::~GameObject() {}
/**
 * StartUp the game object
 */
void GameObject::StartUp() {}
/**
 * ShutDown the game object by clearing the components map
 */
void GameObject::ShutDown() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->ShutDown();
        RemoveComponent(it->first);
    }
}
/**
 * Update the game object by iterating through all the components and
 * calling their Update function. The components are stored in a ordered
 * map, with the key being the id of the component. The order to update
 * the components is important, as some components may depend
 */
void GameObject::Update() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->Update();
    }
}
/**
 * Render the game object by iterating through all the components and
 * calling their Render function. The components are stored in a ordered
 * map, with the key being the id of the component. The order to render
 * the components is important, as some components may depend
 */
void GameObject::Render() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->Render();
    }
}
/**
 * Add a component to the game object. The component name is used as the
 * key for the component in the map. It must order the components in the
 * right place for the Update and Render functions to work correctly.
 */
void GameObject::AddComponent(std::string componentName,
                              std::shared_ptr<Component> component) {
    if (component->GetType() == CollisionComponent_TYPE) {
        m_collisionComponent = component;
    }
    m_components.emplace(componentName, component);
}
/**
 * Remove a component from the game object given the component name
 */
void GameObject::RemoveComponent(std::string componentName) {
    m_components.erase(componentName);
}
/**
 * Get a component from the game object given the component name
 */
std::shared_ptr<Component> GameObject::GetComponent(std::string componentName) {
    return m_components[componentName];
}

// template <typename T>
// std::vector<std::shared_ptr<T>> GameObject::GetComponents() {
//     std::vector<std::shared_ptr<T>> components;
//     for (auto it = m_components.begin(); it != m_components.end(); it++) {
//         std::shared_ptr<T> component =
//         std::dynamic_pointer_cast<T>(it->second); if (component != nullptr) {
//             components.push_back(component);
//         }
//     }
//     return components;
// }
/**
 * Get the collision component of the game object
 */
std::shared_ptr<Component> GameObject::GetCollisionComponent() {
    return m_collisionComponent;
}