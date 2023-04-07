#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include "./Components/Component.hpp"
#include "./ResourceManager.hpp"

// a new component or just use SpriteCOmponent?
class CameraComponent : public Component
{
public:
    CameraComponent( );
    ~CameraComponent();

    void Update() override;
    void Render() override;

    void SetCamera();

private:

};

#endif
