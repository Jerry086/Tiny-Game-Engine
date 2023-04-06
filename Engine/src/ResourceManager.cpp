#include "ResourceManager.hpp"

#include <iostream>
#include <iterator>

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

ResourceManager &ResourceManager::instance()
{
    static ResourceManager instance;
    return instance;
}

// search if this surface has been loaded, and then
// only call SDL_LoadBMP if that resource does not previously exist.
void ResourceManager::LoadSurface(std::string image_filename)
{
    auto it = surfaceMap.find(image_filename);
    // check if resource is already loaded
    if (it != surfaceMap.end())
    {
        // increment resource counter
        ++it->second.second;
    }
    else
    {
        // load new resource
        SDL_Surface *spriteSheet = SDL_LoadBMP(image_filename.c_str());
        if (spriteSheet == nullptr)
        {
            std::cerr << image_filename << " not found!\n";
            return;
        }
        std::cout << "New SDL_Surface copy of " << image_filename
                  << " has been loaded\n";
        surfaceMap.emplace(image_filename, std::make_pair(spriteSheet, 1));
    }
}

// retrieve a loaded surface
SDL_Surface *ResourceManager::GetSurface(std::string image_filename)
{
    auto it = surfaceMap.find(image_filename);
    if (it == surfaceMap.end())
    {
        std::cout << "Resource " << image_filename << " has not been loaded\n";
        return nullptr;
    }
    std::cout << "Retrieved saved SDL_Surface copy of " << image_filename
              << " from GetResource\n";
    return it->second.first;
}

// free a SDL_Surface
void ResourceManager::FreeSurface(std::string image_filename)
{
    auto it = surfaceMap.find(image_filename);
    if (it == surfaceMap.end())
    {
        std::cout << "SDL_Surface of " << image_filename << " does not exist\n";
    }
    else
    {
        // decrement resource counter
        --it->second.second;
        // free SDL_Surface when it is not used by other objects
        if (!it->second.second)
        {
            SDL_FreeSurface(it->second.first);
            it->second.first = nullptr;
            surfaceMap.erase(it);
            std::cout << "SDL_Surface Resource " << it->first
                      << " has been freed\n";
        }
    }
}

// search if this texture has been loaded, and then
// only call SDL_CreateTextureFromSurface if that resource does not previously
// exist.
void ResourceManager::LoadTexture(std::string image_filename)
{
    auto it = textureMap.find(image_filename);
    // check if resource is already loaded
    if (it != textureMap.end())
    {
        // increment resource counter
        ++it->second.second;
    }
    else
    {
        // create new texture
        SDL_Texture *texture = SDL_CreateTextureFromSurface(
            m_renderer, GetSurface(image_filename));
        if (texture == nullptr)
        {
            std::cerr << "Error creating texture\n";
            return;
        }
        std::cout << "New SDL_Texture copy of " << image_filename
                  << " has been loaded\n";
        textureMap.emplace(image_filename, std::make_pair(texture, 1));
    }
}

// retrieve a loaded texture
SDL_Texture *ResourceManager::GetTexture(std::string image_filename)
{
    auto it = textureMap.find(image_filename);
    if (it == textureMap.end())
    {
        std::cout << "SDL_Texture Resource " << image_filename
                  << " has not been loaded\n";
        return nullptr;
    }
    std::cout << "Retrieved saved SDL_Texture copy of " << image_filename
              << " from GetResource\n";
    return it->second.first;
}

// destroy a SDL_Texture
void ResourceManager::DestroyTexture(std::string image_filename)
{
    auto it = textureMap.find(image_filename);
    if (it == textureMap.end())
    {
        std::cout << "SDL_Texture of " << image_filename << " does not exist\n";
    }
    else
    {
        // decrement resource counter
        --it->second.second;
        // destroy SDL_Texture when it is not used by other objects
        if (!it->second.second)
        {
            SDL_DestroyTexture(it->second.first);
            it->second.first = nullptr;
            textureMap.erase(it);
            std::cout << "SDL_Texture Resource " << it->first
                      << " has been destroyed\n";
        }
    }
}

int ResourceManager::StartUp(SDL_Renderer *renderer)
{
    m_renderer = renderer;
    return 0;
}

// Kill all resource in resource manager
int ResourceManager::ShutDown()
{
    // Kill all SDL_Surface
    auto it_surface = surfaceMap.begin();
    while (it_surface != surfaceMap.end())
    {
        SDL_FreeSurface(it_surface->second.first);
        it_surface->second.first = nullptr;
        std::cout << "SDL_Surface Resource " << it_surface->first
                  << " has been freed\n";
        it_surface = surfaceMap.erase(it_surface);
    }

    // Kill all SDL_Texture
    auto it_texture = textureMap.begin();
    while (it_texture != textureMap.end())
    {
        SDL_DestroyTexture(it_texture->second.first);
        it_texture->second.first = nullptr;
        std::cout << "SDL_Texture Resource " << it_texture->first
                  << " has been destroyed\n";
        it_texture = textureMap.erase(it_texture);
    }
    return 0;
}
