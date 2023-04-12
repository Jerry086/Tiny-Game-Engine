#ifndef HEALTHBARCOMPONENT_HPP
#define HEALTHBARCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "./ResourceManager.hpp"

// a new component or just use SpriteCOmponent?
class HealthBarComponent : public Component
{
public:
    HealthBarComponent(std::string filename,
                       std::shared_ptr<TransformComponent> transformComponent,
                       int x, int y, int w, int h);
    ~HealthBarComponent();

    int health = 100;
    // 0,20,40,60,80,100
    void SetHealth(int newHealth);
    void Update() override;
    void Render() override;

private:
    // std::shared_ptr<SpriteComponent> m_sprite;
    std::string m_filename;
    std::shared_ptr<TransformComponent> m_transformComponent;
    // An SDL Surface contains pixel data to draw an image
    SDL_Surface *m_spriteSheet = nullptr;
    SDL_Texture *m_texture = nullptr;

    SDL_Rect mSrc;
    SDL_Rect mDest = {100, 100, 100, 100};
};

#endif
