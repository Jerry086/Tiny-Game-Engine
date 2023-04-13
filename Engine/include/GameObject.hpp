#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "./Components/Component.hpp"

class GameObject {
   public:
    GameObject(std::string id);
    ~GameObject();

    void StartUp();
    void ShutDown();

    void Update();
    void Render();

    void AddComponent(std::string componentName,
                      std::shared_ptr<Component> component);
    void RemoveComponent(std::string componentName);
    std::shared_ptr<Component> GetComponent(std::string componentName);

    template <typename T>
    std::vector<std::shared_ptr<T>> GetComponents();

    std::map<std::string, std::shared_ptr<Component>> m_components;

   private:
    // std::map<std::string, Component> m_components;
    std::string gameObject_id;
};

#endif
