#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>

#else // This works for Mac
#include <SDL.h>

#endif

#include "Component.hpp"
#include "ResourceManager.hpp"
#include "TransformComponent.hpp"
#include "ControllerComponent.hpp"
#include "BehaviorComponent.hpp"

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
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
    unsigned int mLastFrame{2};
    unsigned int mNumRows{1};
    unsigned int mNumCols{1};
    unsigned int mCurrentRow{0};
    // An SDL Surface contains pixel data to draw an image
    SDL_Surface *m_spriteSheet = nullptr;
    SDL_Texture *m_texture = nullptr;
    std::shared_ptr<ControllerComponent> m_controller = nullptr;
    std::shared_ptr<BehaviorComponent> m_behavior = nullptr;

    SDL_Rect mSrc{0, 0, 125, 254};
    SDL_Rect mDest;
};

#endif
