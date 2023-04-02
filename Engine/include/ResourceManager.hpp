#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

// I recommend a map for filling in the resource manager
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    // get the only instance of Resource Manager
    static ResourceManager &instance();
    // Load a image on the CPU
    void LoadSurface(std::string image_filename);
    // SDL_Surface Getter of previously loaded image
    SDL_Surface *GetSurface(std::string image_filename);
    // Free a image on the CPU
    void FreeSurface(std::string image_filename);
    // Load a SDL_Texture from a SDL_Surface
    void LoadTexture(std::string image_filename);
    // SDL_Texture Getter of previously loaded texture;
    SDL_Texture *GetTexture(std::string image_filename);
    // Destroy a SDL_Texture on the GPU
    void DestroyTexture(std::string image_filename);
    // Destroy resources in resource manager
    int StartUp(SDL_Renderer *renderer);
    int ShutDown();

private:
    // unordered_map data structure to search if a resource has been previously loaded
    std::unordered_map<std::string, std::pair<SDL_Surface *, int>> surfaceMap;
    std::unordered_map<std::string, std::pair<SDL_Texture *, int>> textureMap;
    // private constructor
    ResourceManager();
    // destructor
    ~ResourceManager();
    // avoid copy constructor
    ResourceManager(const ResourceManager &) = delete;
    // avoid assignment operator
    ResourceManager &operator=(const ResourceManager &) = delete;
    SDL_Renderer *m_renderer;
};

#endif
