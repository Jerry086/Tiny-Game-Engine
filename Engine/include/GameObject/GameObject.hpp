#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <string>

#include "Component.hpp"
#include "SpriteComponent.hpp"
#include "TileMapComponent.hpp"

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

class GameObject{
    public:
        GameObject(std::string name);
        ~GameObject();

        void Update(int x, int y, int frame);
        void Render(SDL_Renderer* ren);
        // parameters
        void AddTileMapComponent(std::string tileSheetFileName, int rows, int cols, 
int _TileWidth, int _TileHeight, int _mapX, int _mapY,SDL_Renderer* ren);
        void AddSpriteComponent2D(std::string filename,SDL_Renderer* ren);

        void SetPosition(float x, float y);
        void MoveObject(float left, float right);
    // Note: You may want to add member functions like 'Update' or 'Render'
    // Note: You may want to add member functions like "AddComponent" or "RemoveComponent"
    
    private:
        std::vector<std::shared_ptr<Component>> m_components;
        std::string m_name;
};


#endif
