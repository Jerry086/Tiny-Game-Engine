#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include "Component.hpp"
#include "Vec.hpp"
#include "TransformComponent.hpp"


class ControllerComponent : public Component
{
public:
    CollisionComponent();
    ~CollisionComponent();

    // Check collision then call transform component to update position
    void CheckCollisionWithWidow();
    void CheckCollisionWithTile();

private:
    TransformComponent *m_transformer;

};

#endif
