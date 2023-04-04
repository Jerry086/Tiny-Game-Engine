#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>

#else  // This works for Mac
#include <SDL.h>

#endif

#include "Component.hpp"
#include "ResourceManager.hpp"
#include "TransformComponent.hpp"

/**
 * A small class to demonstrate loading sprites.
 * Sprite sheets are often used for loading characters,
 * environments, icons, or other images in a game.
 */
class SpriteComponent : public Component {
   public:
    /**
     * Constructor
     */
    SpriteComponent(std::string filename,
                    std::shared_ptr<TransformComponent> transformComponent,
                    int x, int y, int w, int h, int frames, int numRows,
                    int numCols);
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
    std::shared_ptr<TransformComponent> m_transformComponent;
    unsigned int mCurrentFrame{0};
    unsigned int mLastFrame{7};
    unsigned int mNumRows{1};
    unsigned int mNumCols{1};
    // An SDL Surface contains pixel data to draw an image
    SDL_Surface *m_spriteSheet = nullptr;
    SDL_Texture *m_texture = nullptr;

    SDL_Rect mSrc;
    SDL_Rect mDest;
};

#endif
