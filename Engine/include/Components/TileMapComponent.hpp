#ifndef TILEMAPCOMPONENT_H
#define TILEMAPCOMPONENT_H

#include <string>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>

#else  // This works for Mac
#include <SDL.h>

#endif

#include "./Services/ResourceManager.hpp"
#include "Component.hpp"

/**
 * This is a minimal implementation of a TileMap
 */
class TileMapComponent : public Component {
   public:
    /**
     * Constructor for a tilemap
     */
    TileMapComponent(std::string tileSheetFileName, int rows, int cols,
                     int _TileWidth, int _TileHeight, int _mapX, int _mapY);
    /**
     * Destructor for a tilemap
     */
    ~TileMapComponent();
    /**
     * Temporary function for generating a simple
     * map to display some tiles
     */
    void GenerateSimpleMap();
    /**
     * Function for printing text to console
     */
    void PrintMap();
    /**
     * Set the 'type' of tile at an x and y position
     */
    void SetTile(int x, int y, int type);
    /**
     * Return the tile type at an x and y position
     */
    int GetTileType(int x, int y);
    /**
     * Draw all of the tiles in the tilemap
     */
    void Render() override;

    void Update() override;

    void SetPosition(float x, float y);

    void MoveObject(float left, float right);

   private:
    // Dimensions of our TileMap and individual tiles.
    // Used for spiltting up the sprite sheet
    int m_Rows;
    int m_Cols;
    // How big each tile is.
    int m_TileWidth;
    int m_TileHeight;
    // size of our tilemap
    int m_MapX;
    int m_MapY;
    // Where our TileMap is rendered
    // An SDL Surface contains pixel data to draw our TileMap
    SDL_Surface *m_TileSpriteSheet;
    SDL_Texture *m_Texture;
    // Stores our tile types
    int *m_Tiles;
};

#endif
