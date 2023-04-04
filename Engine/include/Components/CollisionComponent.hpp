#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include "./Components/Component.hpp"
#include "Vec.hpp"
#include "./Components/TransformComponent.hpp"
#include "GameObjectManager.hpp"

class CollisionComponent : public Component
{
public:
    CollisionComponent(bool isStatic, int w, int h);
    ~CollisionComponent();

    Vec2 CheckCollision(std::shared_ptr<CollisionComponent> other);
    void Update();



    // Check collision then call transform component to update position
    // void CheckCollisionWithWidow();
    // void CheckCollisionWithTile();

TransformComponent *m_transformer;
private:
    
    bool isStatic;
    int height = 0;
    int width = 0;
};

#endif
