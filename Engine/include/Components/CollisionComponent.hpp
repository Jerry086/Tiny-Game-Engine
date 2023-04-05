#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include "./Components/Component.hpp"
#include "Vec.hpp"
#include "./Components/ControllerComponent.hpp"
#include "./Components/TransformComponent.hpp"
#include "GameObjectManager.hpp"

enum ObjectType
{
    player,
    wall,
    enemy,
    interactable
};

class CollisionComponent : public Component
{
public:
    CollisionComponent(std::string objectType, std::shared_ptr<TransformComponent> transformer, int w, int h);
    ~CollisionComponent();

    Vec2 CheckCollision(std::shared_ptr<CollisionComponent> other);
    void Update();

    // Check collision then call transform component to update position
    // void CheckCollisionWithWidow();
    // void CheckCollisionWithTile();

    std::shared_ptr<TransformComponent> m_transformer;
    std::string m_objectType;

private:
    int m_height = 0;
    int m_width = 0;
    ObjectType GetType(std::string inString);
    std::shared_ptr<ControllerComponent> m_controller = nullptr;
};

#endif
