#ifndef HEALTHBARCOMPONENT_HPP
#define HEALTHBARCOMPONENT_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "ResourceManager.hpp"

#define HealthBar_Width 64
#define HealthBar_Height 5
/**
 * @brief The HealthBarComponent class
 *
 * A component that renders a health bar
 */
class HealthBarComponent : public Component
{
public:
    /**
     * @brief Constructor
     * @param filename The filename of the sprite sheet
     * @param transformComponent The transform component
     * @param w The width of the sprite
     * @param h The height of the sprite
     * @param frames The number of frames in the sprite sheet
     * @param numRows The number of rows in the sprite sheet
     * @param numCols The number of columns in the sprite sheet
     */
    HealthBarComponent(std::string filename,
                       std::shared_ptr<TransformComponent> transformComponent,
                       int w, int h, int frames, int numRows, int numCols);
    /**
     * @brief Destructor
     */
    ~HealthBarComponent();
    /**
     * @brief ShutDown the component
     */
    void ShutDown() override;
    /**
     * @brief Set the health of the health bar
     * @param newHealth The new health
     */
    void SetHealth(int newHealth);
    /**
     * @brief Update the component
     */
    void Update() override;
    /**
     * @brief Render the component
     */
    void Render() override;
    /**
     * @brief Getter of the component type
     * @return The type of the component
     */
    int GetType() override;

private:
    unsigned int health{5};
    unsigned int m_currentFrame{0};
    unsigned int m_lastFrame{1};
    unsigned int m_numRows{0};
    unsigned m_numCols{0};
    const int m_type = HealthBarComponent_TYPE;
    std::string m_filename;
    std::shared_ptr<TransformComponent> m_transformComponent;
    SDL_Surface *m_spriteSheet = nullptr;
    SDL_Texture *m_texture = nullptr;
    SDL_Rect mSrc;
    SDL_Rect mDest;
};

#endif
