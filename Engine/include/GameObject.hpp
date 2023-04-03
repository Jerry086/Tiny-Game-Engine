#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <map>
#include <memory>
#include <string>

#include "./Components/Component.hpp"

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else  // This works for Mac
#include <SDL.h>
#endif

class GameObject {
   public:
    GameObject(std::string id);
    ~GameObject();

    void StartUp();
    void ShutDown();

    void Update();
    void Render();

    // void AddComponent(std::string
    // componentName,std::shared_ptr<Component>component);
    void AddComponent(std::string componentName,
                      std::shared_ptr<Component> component);
    void RemoveComponent(std::string componentName);

   private:
    // std::map<std::string, Component> m_components;
    std::map<std::string, std::shared_ptr<Component>> m_components;
    std::string gameObject_id;
};

#endif
