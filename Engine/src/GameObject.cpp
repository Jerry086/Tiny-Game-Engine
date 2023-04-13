#include "GameObject.hpp"

GameObject::GameObject(std::string id) : gameObject_id(id) {}

GameObject::~GameObject() {}

void GameObject::StartUp() {}

void GameObject::ShutDown() {}

void GameObject::Update() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->Update();
    }
}

void GameObject::Render() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->Render();
    }
}

void GameObject::AddComponent(std::string componentName,
                              std::shared_ptr<Component> component) {
    m_components.emplace(componentName, component);
}

void GameObject::RemoveComponent(std::string componentName) {
    m_components.erase(componentName);
}

std::shared_ptr<Component> GameObject::GetComponent(std::string componentName) {
    return m_components[componentName];
}

template <typename T>
std::vector<std::shared_ptr<T>> GameObject::GetComponents() {
    std::vector<std::shared_ptr<T>> components;
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(it->second);
        if (component != nullptr) {
            components.push_back(component);
        }
    }
    return components;
}