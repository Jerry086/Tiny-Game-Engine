#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <string>
#include <unordered_map>

class ServiceLocator;

/**
 * @brief The ResourceManager class
 *
 * Singleton class that manages all resources, including surfaces and textures.
 */
class ResourceManager {
    friend class ServiceLocator;

   public:
    /**
     * @brief Obtain the instance of the resource manager
     */
    static ResourceManager &instance();
    /**
     * @brief Load a SDL_Surface from a image file
     * @param image_filename The path to the image file
     */
    void LoadSurface(std::string image_filename);
    /**
     * @brief Get a previously loaded SDL_Surface
     * @param image_filename The path to the image file
     */
    SDL_Surface *GetSurface(std::string image_filename);
    /**
     * @brief Free a previously loaded SDL_Surface
     */
    void FreeSurface(std::string image_filename);
    /**
     * @brief Load a SDL_Texture from a image file
     * @param image_filename The path to the image file
     */
    void LoadTexture(std::string image_filename);
    /**
     * @brief Get a previously loaded SDL_Texture
     * @param image_filename The path to the image file
     */
    SDL_Texture *GetTexture(std::string image_filename);
    /**
     * @brief Destroy a previously loaded SDL_Texture
     * @param image_filename The path to the image file
     */
    void DestroyTexture(std::string image_filename);
    /**
     * @brief Get the SDL_Renderer
     */
    SDL_Renderer *GetRenderer();
    /**
     * @brief Initialize the resource manager
     * @param renderer The SDL_Renderer to use
     */
    int StartUp(SDL_Renderer *renderer);
    /**
     * @brief Destroy all resources
     */
    int ShutDown();

   private:
    SDL_Renderer *m_renderer;
    std::unordered_map<std::string, std::pair<SDL_Surface *, int>> surfaceMap;
    std::unordered_map<std::string, std::pair<SDL_Texture *, int>> textureMap;
    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager &) = delete;
    ResourceManager &operator=(const ResourceManager &) = delete;
};

#endif
