#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Component.hpp"
#include "ResourceManager.hpp"
#include "TransformComponent.hpp"
#include "ControllerComponent.hpp"
#include "BehaviorComponent.hpp"

const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

/**
 * The SpriteComponent class that renders a sprite to the screen.
 */
class SpriteComponent : public Component
{
public:
    /**
     * Constructor
     * @param filename The filename of the sprite
     * @param transformComponent The transform component that defines the position
     * @param x The x position of the sprite
     * @param y The y position of the sprite
     * @param w The width of the sprite
     *  @param h The height of the sprite
     * @param frames The number of frames in the sprite
     * @param numRows The number of rows in the sprite
     * @param numCols The number of columns in the sprite
     */
    SpriteComponent(std::string filename,
                    std::shared_ptr<TransformComponent> transformComponent,
                    int x, int y, int w, int h, int frames, int numRows,
                    int numCols);
    /**
     * Destructor
     */
    ~SpriteComponent();
    /**
     * @brief Shutdown the sprite component
     */
    void ShutDown() override;
    /**
     * @brief Update the sprite series and frame
     */
    void Update() override;
    /**
     * Render the sprite
     */
    void Render() override;
    /**
     * Getter of the component type
     * @return The type of the component
     */
    int GetType() override;

private:
    std::string m_filename;
    unsigned int mCurrentFrame{0};
    unsigned int mLastFrame{1};
    unsigned int mNumRows{1};
    unsigned int mNumCols{1};
    unsigned int mCurrentRow{0};
    const int m_type = SpriteComponent_TYPE;
    std::shared_ptr<TransformComponent> m_transformComponent;
    std::shared_ptr<ControllerComponent> m_controller = nullptr;
    std::shared_ptr<BehaviorComponent> m_behavior = nullptr;
    SDL_Surface *m_spriteSheet = nullptr;
    SDL_Texture *m_texture = nullptr;
    SDL_Rect mSrc{0, 0, 125, 254};
    SDL_Rect mDest;
};

#endif
