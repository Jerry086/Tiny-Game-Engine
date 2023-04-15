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

#include "ResourceManager.hpp"
#include "ServiceLocator.hpp"
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

   private:
    int screenHeight;
    int screenWidth;
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
};

/**
 * Constructor
 * @param w The width of the window
 * @param h The height of the window
 */
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h)
    : screenWidth(w), screenHeight(h) {
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError()
                    << "\n";
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("Lab", 100, 100, screenWidth, screenHeight,
                                   SDL_WINDOW_SHOWN);

        // Check if Window did not create.
        if (gWindow == nullptr) {
            errorStream << "Window could not be created! SDL Error: "
                        << SDL_GetError() << "\n";
            success = false;
        }

        // Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        // Check if Renderer did not create.
        if (gRenderer == nullptr) {
            errorStream << "Renderer could not be created! SDL Error: "
                        << SDL_GetError() << "\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the
    // constructor.
    if (!success) {
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to "
                       "initialize!\n";
        std::string errors = errorStream.str();
        SDL_Log("%s\n", errors.c_str());
    } else {
        SDL_Log(
            "SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, "
            "errors detected during initialization\n\n");
    }
    // Initialize the resource manager
    ServiceLocator::RegisterService<ResourceManager>();
    ServiceLocator::GetService<ResourceManager>().StartUp(gRenderer);
    // ResourceManager::instance().StartUp(gRenderer);
}
/**
 * Destructor
 * Proper shutdown of SDL and destroy initialized objects
 */
SDLGraphicsProgram::~SDLGraphicsProgram() {
    ResourceManager::instance().ShutDown();
    // Destroy Renderer
    SDL_DestroyRenderer(gRenderer);
    // Destroy window
    SDL_DestroyWindow(gWindow);
    // Point to NULL to ensure it points to nothing.
    gWindow = nullptr;
    gRenderer = nullptr;
    // Quit SDL subsystems
    SDL_Quit();
}

/**
 * Clear the screen with a black background for rendering
 * Set the color to white for drawing
 */
void SDLGraphicsProgram::clear() {
    SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}
/**
 * Flip the back buffer to the front
 */
void SDLGraphicsProgram::flip() { SDL_RenderPresent(gRenderer); }
/**
 * Delay the program for a given number of milliseconds
 */
void SDLGraphicsProgram::delay(int milliseconds) { SDL_Delay(milliseconds); }
/**
 * Get the SDL_Window
 */
SDL_Window *SDLGraphicsProgram::getSDLWindow() { return gWindow; }
/**
 * Draw a white rectangle to the screen
 */
void SDLGraphicsProgram::DrawRectangle(int x, int y, int w, int h) {
    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(gRenderer, &fillRect);
}
/**
 * Draw a point to the screen
 */
void SDLGraphicsProgram::DrawPoint(int x, int y) {
    SDL_RenderDrawPoint(gRenderer, x, y);
}

#endif