#include "./Services/ResourceManager.hpp"

#include <iostream>
#include <iterator>

/**
 * Destructor
 */
ResourceManager::~ResourceManager() {}
/**
 * Get the instance of the ResourceManager
 */
ResourceManager &ResourceManager::instance() {
    static ResourceManager instance;
    return instance;
}
/**
 * Search if the image has been loaded
 * Call SDL_LoadBMP if that resource does not previously exist.
 * Otherwise, increment the reference count.
 */
void ResourceManager::LoadSurface(std::string image_filename) {
    auto it = surfaceMap.find(image_filename);
    if (it != surfaceMap.end()) {
        ++it->second.second;
    } else {
        SDL_Surface *spriteSheet = SDL_LoadBMP(image_filename.c_str());
        if (spriteSheet == nullptr) {
            std::cerr << image_filename << " not found!\n";
            return;
        }
        surfaceMap.emplace(image_filename, std::make_pair(spriteSheet, 1));
    }
}

/**
 * Retrieve a loaded SDL_Surface given the image filename as a key
 */
SDL_Surface *ResourceManager::GetSurface(std::string image_filename) {
    auto it = surfaceMap.find(image_filename);
    if (it == surfaceMap.end()) {
        std::cout << "Resource " << image_filename << " has not been loaded\n";
        return nullptr;
    }
    return it->second.first;
}

/**
 * Free a SDL_Surface given the image filename as a key
 * Decrement the reference count if the resource is still in use
 */
void ResourceManager::FreeSurface(std::string image_filename) {
    auto it = surfaceMap.find(image_filename);
    if (it == surfaceMap.end()) {
        std::cout << "SDL_Surface of " << image_filename << " does not exist\n";
    } else {
        --it->second.second;
        if (!it->second.second) {
            SDL_FreeSurface(it->second.first);
            it->second.first = nullptr;
            surfaceMap.erase(it);
        }
    }
}

/**
 * Search if the texture has been loaded
 * Load the texture if that resource does not previously exist.
 * Otherwise, increment the reference count.
 */
void ResourceManager::LoadTexture(std::string image_filename) {
    auto it = textureMap.find(image_filename);
    if (it != textureMap.end()) {
        ++it->second.second;
    } else {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(
            m_renderer, GetSurface(image_filename));
        if (texture == nullptr) {
            std::cerr << "Error creating texture\n";
            return;
        }
        textureMap.emplace(image_filename, std::make_pair(texture, 1));
    }
}

/**
 * Retrieve a loaded SDL_Texture given the image filename as a key
 */
SDL_Texture *ResourceManager::GetTexture(std::string image_filename) {
    auto it = textureMap.find(image_filename);
    if (it == textureMap.end()) {
        std::cout << "SDL_Texture Resource " << image_filename
                  << " has not been loaded\n";
        return nullptr;
    }
    return it->second.first;
}

/**
 * Destroy a SDL_Texture given the image filename as a key
 * Decrement the reference count if the resource is still in use
 */
void ResourceManager::DestroyTexture(std::string image_filename) {
    auto it = textureMap.find(image_filename);
    if (it == textureMap.end()) {
        std::cout << "SDL_Texture of " << image_filename << " does not exist\n";
    } else {
        --it->second.second;
        if (!it->second.second) {
            SDL_DestroyTexture(it->second.first);
            it->second.first = nullptr;
            textureMap.erase(it);
        }
    }
}
/**
 * Get the renderer
 */
SDL_Renderer *ResourceManager::GetRenderer() { return m_renderer; }
/**
 * Set the renderer and initialize the resource manager
 */
int ResourceManager::StartUp(SDL_Renderer *renderer) {
    if (renderer == nullptr) {
        std::cerr << "Renderer not found!\n";
        return -1;
    }
    m_renderer = renderer;
    return 0;
}

void ResourceManager::StartUp() {
    if (m_renderer == nullptr) {
        std::cerr << "Renderer not found!\n";
    }
}
/**
 * Free all resources in the resource manager
 */
void ResourceManager::ShutDown() {
    auto it_surface = surfaceMap.begin();
    while (it_surface != surfaceMap.end()) {
        SDL_FreeSurface(it_surface->second.first);
        it_surface->second.first = nullptr;
        it_surface = surfaceMap.erase(it_surface);
    }

    auto it_texture = textureMap.begin();
    while (it_texture != textureMap.end()) {
        SDL_DestroyTexture(it_texture->second.first);
        it_texture->second.first = nullptr;
        it_texture = textureMap.erase(it_texture);
    }
}
