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

class CollisionComponent : public Component
{
public:
    CollisionComponent();
    ~CollisionComponent();
    void Update(){};

    // Check collision then call transform component to update position
    // void CheckCollisionWithWidow();
    // void CheckCollisionWithTile();

private:
    TransformComponent *m_transformer;
};

#endif
