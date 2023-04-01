#ifndef HEALTHBARCOMPONENT_HPP
#define HEALTHBARCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include "./Components/Component.hpp"
#include "Vec.hpp"

// a new component or just use SpriteCOmponent?
class HealthBarComponent : public Component
{
public:
    HealthBarComponent(){};
    ~HealthBarComponent(){};
    void Update(){};

private:
};

#endif
