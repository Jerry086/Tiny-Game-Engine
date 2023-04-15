#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "./Services/GameManager.hpp"
#include "./Services/InputManager.hpp"
#include "./Services/ResourceManager.hpp"
#include "./Services/SDLWrapper.hpp"
#include "./Services/ServiceLocator.hpp"
#include "./Services/VariableManager.hpp"
#include "Vec.hpp"

/**
 * The SDLGraphicsProgram class that handles all graphics.
 */
class SDLGraphicsProgram {
   public:
    /**
     * Constructor
     * @param w The width of the window
     * @param h The height of the window
     */
    SDLGraphicsProgram(int w, int h);
    /**
     * Destructor
     */
    ~SDLGraphicsProgram();
    /**
     * Clear the screen for rendering
     */
    void clear();
    /**
     * Flip the back buffer to the front
     */
    void flip();
    /**
     * Delay the program for a given number of milliseconds
     * @param milliseconds The number of milliseconds to delay
     */
    void delay(int milliseconds);
    /**
     * Get the SDL_Window
     */
    SDL_Window *getSDLWindow();
    /**
     * Draw a rectangle to the screen
     * @param x The x coordinate of the rectangle
     * @param y The y coordinate of the rectangle
     * @param w The width of the rectangle
     * @param h The height of the rectangle
     */
    void DrawRectangle(int x, int y, int w, int h);
    /**
     * Draw a point to the screen
     * @param x The x coordinate of the point
     * @param y The y coordinate of the point
     */
    void DrawPoint(int x, int y);

    void ShutDown();

   private:
    int screenHeight;
    int screenWidth;
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
};

#endif