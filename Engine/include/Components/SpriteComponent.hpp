#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

#include "IGraphicsEngineRenderer.hpp"
#include "./Components/Component.hpp"
#include "Vec.hpp"

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
    SpriteComponent();
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
    void Update(){};
    /**
     * Render the sprite
     */
    void Render();
    /**
     * Load a sprite
     */
    void LoadImage(std::string filePath, SDL_Renderer *ren);

    void MoveObject(float left, float right);

private:
    Vec2 mPosition;
    unsigned int mCurrentFrame{0};
    unsigned int mLastFrame{7};
    // An SDL Surface contains pixel data to draw an image
    SDL_Surface *mSpriteSheet = nullptr;
    SDL_Texture *mTexture = nullptr;

    SDL_Rect mSrc;
    SDL_Rect mDest;
};

#endif
