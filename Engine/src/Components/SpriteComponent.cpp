#include "./Components/SpriteComponent.hpp"

/**
 * Constructor
 */
SpriteComponent::SpriteComponent(
    std::string filename, std::shared_ptr<TransformComponent> transformer,
    int x, int y, int w, int h, int frames, int numRows, int numCols)
    : m_filename(filename),
      m_transformComponent(transformer),
      mLastFrame(frames),
      mNumRows(numRows),
      mNumCols(numCols) {
    ServiceLocator::GetService<ResourceManager>().LoadSurface(filename);
    m_spriteSheet =
        ServiceLocator::GetService<ResourceManager>().GetSurface(filename);
    ServiceLocator::GetService<ResourceManager>().LoadTexture(filename);
    m_texture =
        ServiceLocator::GetService<ResourceManager>().GetTexture(filename);
    mSrc.x = x + m_srcXOffset;
    mSrc.y = y + m_srcYOffset;
    mSrc.w = w;
    mSrc.h = h;

    mDest.w = RENDER_WIDTH;
    mDest.h = RENDER_HEIGHT;

    if (transformer->m_controller != nullptr) {
        m_controller = transformer->m_controller;
    } else if (transformer->m_behavior != nullptr) {
        m_behavior = transformer->m_behavior;
    }
}

SpriteComponent::SpriteComponent(
    std::string filename, std::shared_ptr<TransformComponent> transformer,
    int x, int y, int w, int h, int frames, int numRows, int numCols,
    int forceScreenWidth, int forceScreenHeight)
    : SpriteComponent(filename, transformer, x, y, w, h, frames, numRows,
                      numCols) {
    mDest.w = forceScreenWidth;
    mDest.h = forceScreenHeight;
}

SpriteComponent::SpriteComponent(
    std::string filename, std::shared_ptr<TransformComponent> transformer,
    int x, int y, int w, int h, int frames, int numRows, int numCols,
    int forceScreenWidth, int forceScreenHeight, int srcXOffset, int srcYOffset)
    : SpriteComponent(filename, transformer, x, y, w, h, frames, numRows,
                      numCols, forceScreenWidth, forceScreenHeight) {
    m_srcXOffset = srcXOffset;
    m_srcYOffset = srcYOffset;
}

/**
 * Destructor
 */
SpriteComponent::~SpriteComponent() {}

/**
 * Shutdown the sprite component
 * Free the surface and texture by ResourceManager
 */
void SpriteComponent::ShutDown() {
    ServiceLocator::GetService<ResourceManager>().FreeSurface(m_filename);
    m_spriteSheet = nullptr;
    ServiceLocator::GetService<ResourceManager>().DestroyTexture(m_filename);
    m_texture = nullptr;
}

/**
 * Update the sprite series and frame
 * The sprite series is determined by the direction of the controller or
 * behavior Otherwise, the sprite sheet is treated as one series
 */
void SpriteComponent::Update() {
    if (m_behavior != nullptr) {
        if (m_behavior->GetDirectionX() > 0) {
            mSpriteSeries = RIGHT;
        } else if (m_behavior->GetDirectionX() < 0) {
            mSpriteSeries = LEFT;
        } else if (m_behavior->GetDirectionY() > 0) {
            mSpriteSeries = DOWN;
        } else if (m_behavior->GetDirectionY() < 0) {
            mSpriteSeries = UP;
        }
    } else if (m_controller != nullptr) {
        if (m_controller->GetDirectionX() > 0) {
            mSpriteSeries = RIGHT;
        } else if (m_controller->GetDirectionX() < 0) {
            mSpriteSeries = LEFT;
        } else if (m_controller->GetDirectionY() > 0) {
            mSpriteSeries = DOWN;
        } else if (m_controller->GetDirectionY() < 0) {
            mSpriteSeries = UP;
        }
    }

    // The part of the image that we want to render, 0-indexed
    mCurrentFrame++;
    mCurrentFrame = mCurrentFrame % mLastFrame;

    // Select specific series of sprite sheet
    if (m_behavior != nullptr || m_controller != nullptr) {
        mSrc.x = mCurrentFrame * mSrc.w;
        mSrc.y = mSpriteSeries * mSrc.h;
    } else {
        mSrc.x = (mCurrentFrame % mNumCols) * mSrc.w;
        mSrc.y = (mCurrentFrame / mNumCols) * mSrc.h;
    }

    // The part of the screen that we want to render to
    mDest.x = m_transformComponent->m_position.x;
    mDest.y = m_transformComponent->m_position.y;
    // mDest.w = RENDER_WIDTH;
    // mDest.h = RENDER_HEIGHT;
}

/**
 * Render the sprite to the screen
 */
void SpriteComponent::Render() {
    SDL_Renderer *ren =
        ServiceLocator::GetService<ResourceManager>().GetRenderer();
    SDL_RenderCopy(ren, m_texture, &mSrc, &mDest);
}

/**
 * Getter of the component type
 */
int SpriteComponent::GetType() { return m_type; }
