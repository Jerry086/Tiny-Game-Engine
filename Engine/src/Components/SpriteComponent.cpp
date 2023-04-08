#include "./Components/SpriteComponent.hpp"

SpriteComponent::SpriteComponent(
    std::string filename, std::shared_ptr<TransformComponent> transformer,
    int x, int y, int w, int h, int frames, int numRows, int numCols)
    : m_filename(filename),
      m_transformComponent(transformer),
      mLastFrame(frames),
      mNumRows(numRows),
      mNumCols(numCols)
{
    ResourceManager::instance().LoadSurface(filename);
    m_spriteSheet = ResourceManager::instance().GetSurface(filename);
    ResourceManager::instance().LoadTexture(filename);
    m_texture = ResourceManager::instance().GetTexture(filename);
    mSrc.x = x;
    mSrc.y = y;
    mSrc.w = w;
    mSrc.h = h;
}

// TODO: move texture unloading to shutdown method instead of destructor
SpriteComponent::~SpriteComponent()
{
    // ResourceManager::instance().FreeSurface(m_filename);
    // m_spriteSheet = nullptr;
    // ResourceManager::instance().DestroyTexture(m_filename);
    // m_texture = nullptr;
}

// Set the sprite position
void SpriteComponent::SetPosition(float x, float y)
{
    m_transformComponent->m_position.x = x;
    m_transformComponent->m_position.y = y;
}

void SpriteComponent::Update()
{
    // The part of the image that we want to render
    mCurrentFrame = (mCurrentFrame + 1) % mLastFrame;
    // if (mCurrentFrame >= mLastFrame) {
    //     mCurrentFrame = 0;
    // }

    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
    // how to iterate through sprite sheet?
    // TODO: fix magic number
    mSrc.x = (mCurrentFrame % mNumRows) * mSrc.w;
    mSrc.y = (mCurrentFrame % mNumCols) * mSrc.h;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.
    // std::cout << "x: " << m_transformComponent->m_position.x << std::endl;
    mDest.x = m_transformComponent->m_position.x;
    mDest.y = m_transformComponent->m_position.y;
    mDest.w = 64;
    mDest.h = 64;
}

void SpriteComponent::Render()
{
    // TODO: ugly, find a better way
    // How to get the renderer???
    SDL_Renderer *ren = ResourceManager::instance().m_renderer;
    SDL_RenderCopy(ren, m_texture, &mSrc, &mDest);
}
