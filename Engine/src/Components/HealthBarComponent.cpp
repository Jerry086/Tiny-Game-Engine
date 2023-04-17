#include "./Components/HealthBarComponent.hpp"

#include "./Services/ServiceLocator.hpp"

/**
 * Constructor
 */
HealthBarComponent::HealthBarComponent(
    std::string filename,
    std::shared_ptr<TransformComponent> transformComponent, int w, int h,
    int frames, int numRows, int numCols)
    : m_filename(filename),
      m_transformComponent(transformComponent),
      m_lastFrame(frames),
      m_numRows(numRows),
      m_numCols(numCols) {
    ServiceLocator::GetService<ResourceManager>().LoadSurface(filename);
    m_spriteSheet =
        ServiceLocator::GetService<ResourceManager>().GetSurface(filename);
    ServiceLocator::GetService<ResourceManager>().LoadTexture(filename);
    m_texture =
        ServiceLocator::GetService<ResourceManager>().GetTexture(filename);
    mSrc.x = 0;
    mSrc.y = 0;
    mSrc.w = w;
    mSrc.h = h;
}
/**
 * Destructor
 */
HealthBarComponent::~HealthBarComponent() {}
/**
 * ShutDown the component
 * Free the surface and texture by ResourceManager
 */
void HealthBarComponent::ShutDown() {
    SDL_FreeSurface(m_spriteSheet);
    m_spriteSheet = nullptr;
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
}
/**
 * Update the sprite based on health
 */
void HealthBarComponent::Update() {
    switch (health) {
        case 0:
            m_currentFrame = 0;
            break;
        case 1:
            m_currentFrame = 1;
            break;
        case 2:
            m_currentFrame = 2;
            break;
        case 3:
            m_currentFrame = 3;
            break;
        case 4:
            m_currentFrame = 4;
            break;
        default:
            m_currentFrame = 5;
            break;
    }
    mSrc.x = (m_currentFrame % m_numCols) * mSrc.w;
    mSrc.y = (m_currentFrame / m_numCols) * mSrc.h;

    mDest.x = m_transformComponent->m_position.x;
    mDest.y = m_transformComponent->m_position.y - HealthBar_Height;
    mDest.w = HealthBar_Width;
    mDest.h = HealthBar_Height;
}
/**
 * Render the component to the screen
 */
void HealthBarComponent::Render() {
    SDL_Renderer *ren =
        ServiceLocator::GetService<ResourceManager>().GetRenderer();
    SDL_RenderCopy(ren, m_texture, &mSrc, &mDest);
}
/**
 * Set the health of the health bar
 */
void HealthBarComponent::SetHealth(int newHealth) { health = newHealth; }
/**
 * Getter of the component type
 */
int HealthBarComponent::GetType() { return m_type; }