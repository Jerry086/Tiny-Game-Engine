#include "SDLGraphicsProgram.h"

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

    // TODO Hacky way to get the SDL around
    ServiceLocator::RegisterService<SDLWrapper>();
    ServiceLocator::GetService<SDLWrapper>().StartUp(*this);

    // Initialize the resource manager
    ServiceLocator::RegisterService<ResourceManager>();
    ServiceLocator::GetService<ResourceManager>().StartUp(gRenderer);

    ServiceLocator::RegisterService<InputManager>();
    ServiceLocator::RegisterService<GameManager>();
    ServiceLocator::RegisterService<VariableManager>();
}
/**
 * Destructor
 * Proper shutdown of SDL and destroy initialized objects
 */
SDLGraphicsProgram::~SDLGraphicsProgram() {}

void SDLGraphicsProgram::ShutDown() {
    ServiceLocator::ShutDown();
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
