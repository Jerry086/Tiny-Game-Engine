#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>

#else // This works for Mac
#include <SDL.h>

#endif

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Vec.hpp"
#include "ResourceManager.hpp"
// Purpose:
// This class sets up a full graphics program using SDL
//
//
//
class SDLGraphicsProgram
{
public:
    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Destructor
    ~SDLGraphicsProgram();
    // Setup OpenGL
    bool initGL();
    // Clears the screen
    void clear();
    // Flips to new buffer
    void flip();
    // Delay rendering

    void delay(int milliseconds);

    // loop that runs forever
    void loop();

    // Get Pointer to Window
    SDL_Window *getSDLWindow();
    // Draw a simple rectangle
    void DrawRectangle(int x, int y, int w, int h);
    void DrawPoint(int x, int y);

    std::string getKeyAction();

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    // The window we'll be rendering to
    SDL_Window *gWindow;
    // Our renderer
    SDL_Renderer *gRenderer;
};

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h) : screenWidth(w), screenHeight(h)
{
    // Initialization flag
    bool success = true;
    // String to hold any errors that occur.
    std::stringstream errorStream;
    // The window we'll be rendering to
    gWindow = NULL;
    // Render flag

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("Lab", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

        // Check if Window did not create.
        if (gWindow == NULL)
        {
            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        // Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        // Check if Renderer did not create.
        if (gRenderer == NULL)
        {
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }
    }

    // If initialization did not work, then print out a list of errors in the constructor.
    if (!success)
    {
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors = errorStream.str();
        SDL_Log("%s\n", errors.c_str());
    }
    else
    {
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

    ResourceManager::instance().StartUp(gRenderer);
}

// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram()
{
    ResourceManager::instance().ShutDown();
    // Destroy Renderer
    SDL_DestroyRenderer(gRenderer);
    // Destroy window
    SDL_DestroyWindow(gWindow);
    // Point gWindow to NULL to ensure it points to nothing.
    gWindow = NULL;
    // Quit SDL subsystems
    SDL_Quit();
}

void SDLGraphicsProgram::DrawPoint(int x, int y)
{
    SDL_RenderDrawPoint(gRenderer, x, y);
}

// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::initGL()
{
    // Success flag
    bool success = true;

    return success;
}

// clear
// Clears the screen
void SDLGraphicsProgram::clear()
{
    // Nothing yet!
    SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}
// Flip
// The flip function gets called once per loop
// It swaps out the previvous frame in a double-buffering system
void SDLGraphicsProgram::flip()
{
    // Nothing yet!
    SDL_RenderPresent(gRenderer);
}

void SDLGraphicsProgram::delay(int milliseconds)
{
    SDL_Delay(milliseconds);
}

// Loops forever!
void SDLGraphicsProgram::loop()
{
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // While application is running
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        } // End SDL_PollEvent loop.

        // Update screen of our specified window
        SDL_GL_SwapWindow(getSDLWindow());
    }

    // Disable text input
    SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window *SDLGraphicsProgram::getSDLWindow()
{
    return gWindow;
}

// Okay, render our rectangles!
void SDLGraphicsProgram::DrawRectangle(int x, int y, int w, int h)
{
    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(gRenderer, &fillRect);
}

std::string SDLGraphicsProgram::getKeyAction()
{

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return "exit";
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                return "exit";
            }
            else if (event.key.keysym.sym == SDLK_w)
            {
                return "1,up,0";
            }
            else if (event.key.keysym.sym == SDLK_s)
            {
                return "1,down,0";
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                return "2,up,0";
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                return "2,down,0";
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_w)
            {
                return "1,up,1";
            }
            else if (event.key.keysym.sym == SDLK_s)
            {
                return "1,down,1";
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                return "2,up,1";
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                return "2,down,1";
            }
        }
    }
    SDL_GL_SwapWindow(getSDLWindow());
    return "empty";
}

// Contact CheckPaddleCollision(Ball const &ball, Paddle const &paddle)
// {
//     float ballLeft = ball.position.x;
//     float ballRight = ball.position.x + BALL_WIDTH;
//     float ballTop = ball.position.y;
//     float ballBottom = ball.position.y + BALL_HEIGHT;

//     float paddleLeft = paddle.position.x;
//     float paddleRight = paddle.position.x + PADDLE_WIDTH;
//     float paddleTop = paddle.position.y;
//     float paddleBottom = paddle.position.y + PADDLE_HEIGHT;

//     Contact contact{};

//     if (ballLeft >= paddleRight)
//     {
//         return contact;
//     }

//     if (ballRight <= paddleLeft)
//     {
//         return contact;
//     }

//     if (ballTop >= paddleBottom)
//     {
//         return contact;
//     }

//     if (ballBottom <= paddleTop)
//     {
//         return contact;
//     }

//     float paddleRangeUpper = paddleBottom - (2.0f * PADDLE_HEIGHT / 3.0f);
//     float paddleRangeMiddle = paddleBottom - (PADDLE_HEIGHT / 3.0f);

//     if (ball.velocity.x < 0)
//     {

//         contact.penetration = paddleRight - ballLeft;
//     }
//     else if (ball.velocity.x > 0)
//     {

//         contact.penetration = paddleLeft - ballRight;
//     }

//     if ((ballBottom > paddleTop) && (ballBottom < paddleRangeUpper))
//     {
//         contact.type = 1;
//     }
//     else if ((ballBottom > paddleRangeUpper) && (ballBottom < paddleRangeMiddle))
//     {
//         contact.type = 2;
//     }
//     else
//     {
//         contact.type = 3;
//     }

//     return contact;
// }

// Contact CheckWallCollision(Ball const &ball)
// {
//     float ballLeft = ball.position.x;
//     float ballRight = ball.position.x + BALL_WIDTH;
//     float ballTop = ball.position.y;
//     float ballBottom = ball.position.y + BALL_HEIGHT;

//     Contact contact{};

//     if (ballLeft < 0.0f)
//     {
//         contact.type = 4;
//     }
//     else if (ballRight > WINDOW_WIDTH)
//     {
//         contact.type = 5;
//     }
//     else if (ballTop < 0.0f)
//     {
//         contact.type = 1;
//         contact.penetration = -ballTop;
//     }
//     else if (ballBottom > WINDOW_HEIGHT)
//     {
//         contact.type = 3;
//         contact.penetration = WINDOW_HEIGHT - ballBottom;
//     }

//     return contact;
// }

#endif