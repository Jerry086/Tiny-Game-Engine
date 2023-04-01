#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>

#else // This works for Mac
#include <SDL.h>

#endif

#include "ResourceManager.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class SpriteComponent : public Component
{
public:
    /**
     * Constructor
     */
    SpriteComponent(std::string filename, TransformComponent &transformComponent, int x, int y, int w, int h, int frames);
    /**
     * Constructor
     */
    ~SpriteComponent();
    /**
     * Initialize the sprite
     */
    void SetPosition(float x, float y);
    /**
     * Update the sprites position and frame
     */
    void Update() override;
    /**
     * Render the sprite
     */
    void Render() override;

private:
    std::string m_filename;
    TransformComponent m_transformComponent;
    unsigned int mCurrentFrame{0};
    unsigned int mLastFrame{7};
    // An SDL Surface contains pixel data to draw an image
    SDL_Surface *m_spriteSheet = nullptr;
    SDL_Texture *m_texture = nullptr;

    SDL_Rect mSrc;
    SDL_Rect mDest;
};

#endif
