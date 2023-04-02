#include "GameObject.hpp"

#include <iostream>
GameObject::GameObject(std::string id) { gameObject_id = id; }

GameObject::~GameObject() {}

void GameObject::StartUp() {}

void GameObject::ShutDown() {}

void GameObject::Render() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        it->second->Render();
    }
}

void GameObject::Update() {
    for (auto it = m_components.begin(); it != m_components.end(); it++) {
        std::cout << "GameObject::Update() " << it->first << std::endl;
        it->second->Update();
    }
}

void GameObject::AddComponent(std::string componentName,
                              std::shared_ptr<Component> component) {
    std::cout << "GameObject::AddComponent() - " << componentName << std::endl;
    m_components.emplace(componentName, component);
}

void GameObject::RemoveComponent(std::string componentName) {
    m_components.erase(componentName);
}