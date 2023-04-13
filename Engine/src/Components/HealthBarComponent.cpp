#include "./Components/HealthBarComponent.hpp"

HealthBarComponent::HealthBarComponent(
    std::string filename,
    std::shared_ptr<TransformComponent> transformer, int x, int y,
    int w, int h)
{
    m_transformComponent = transformer;
    ResourceManager::instance().LoadSurface(filename);
    m_spriteSheet = ResourceManager::instance().GetSurface(filename);
    ResourceManager::instance().LoadTexture(filename);
    m_texture = ResourceManager::instance().GetTexture(filename);
    mSrc.x = x;
    mSrc.y = y;
    mSrc.w = w;
    mSrc.h = h;
}

HealthBarComponent::~HealthBarComponent()
{
}

void HealthBarComponent::Update()
{
    // Collision + keyboard detect or simply collision
    mDest.x = m_transformComponent->m_position.x;
    mDest.y = m_transformComponent->m_position.y;
    mDest.w = 128;
    mDest.h = 128;
}

void HealthBarComponent::Render()
{
    SDL_Renderer *ren = ResourceManager::instance().GetRenderer();
    SDL_RenderCopy(ren, m_texture, &mSrc, &mDest);
}

void HealthBarComponent::SetHealth(int newHealth)
{
    health = newHealth;
}