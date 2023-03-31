#include "GameObject.hpp"
#include <iostream>
GameObject::GameObject(std::string name){
    m_name = name;
}

GameObject::~GameObject(){
}

void GameObject:: SetPosition(float x, float y){
    for(int i = 0; i < m_components.size(); i++){
        m_components[i]->SetPosition(x,y);
    }
}

void GameObject:: AddSpriteComponent2D(std::string filename, SDL_Renderer* ren){
    std::shared_ptr<SpriteComponent> sprite2DComponent = 
    std::make_shared<SpriteComponent>();
    sprite2DComponent->LoadImage(filename, ren);
    m_components.push_back(sprite2DComponent);
}

void GameObject:: Render(SDL_Renderer* ren){
    for(int i = 0; i < m_components.size(); i++){
        m_components[i]->Render(ren);
    }
}

void GameObject:: Update(int x, int y, int frame){
        for(int i = 0; i < m_components.size(); i++){
        m_components[i]->Update(x,y,frame);
    }
}

void GameObject:: AddTileMapComponent(std::string tileSheetFileName, int rows, int cols, 
int _TileWidth, int _TileHeight, int _mapX, int _mapY, SDL_Renderer* ren){
    std::shared_ptr<TileMapComponent> tilemap = std::make_shared<TileMapComponent>(tileSheetFileName, rows, cols,_TileWidth,_TileHeight,_mapX,
     _mapY, ren);
     m_components.push_back(tilemap);
}

void GameObject:: MoveObject(float left, float right){
    for(int i = 0; i < m_components.size(); i++){
        m_components[i]->MoveObject(left,right);
    }
}
