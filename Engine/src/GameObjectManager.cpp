#include "Engine.hpp"
#include "SpriteComponent.hpp"
#include "TileMapComponent.hpp"
// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine() {}

// Proper shutdown and destroy initialized objects
Engine::~Engine() {}

// Update SDL
void Engine::Update()
{
    for (GameObject *entity : m_gameObjects)
    {
        entity->Update();
    }
}

// Render
// The render function gets called once per loop
void Engine::Render()
{
    // Set the color of the empty frame buffer
    mRenderer->SetRenderDrawColor(110, 130, 170, 0xFF);
    // Clear the screen to the color of the empty frame buffer
    mRenderer->RenderClear();

    // NOTE: We have to dynamic_cast here, because we do not exactly know the type
    //       of the renderer that is going to 'render' our character.
    //       Polymorphism is being used for our renderer, and we need to thus
    //       determine using dynamic_cast if we can make a successful cast to find
    //       a matching member function that can retrieve a 'renderer' suitable.
    // NOTE: The very fact that I am storing an SDL_Renderer* below completely
    //       defeats the purpose of using the dynamic_cast.
    //       The whole point of the dynamic_cast is so that at run-time we can retrieve a
    //       renderer to draw our characters.
    //       That said, it's just more readable for you to see the dynamic cast here.
    // NOTE: If dynamic_cast fails, you can check at run-time and handle through either an
    //       assertion or exception the behavior.
    SDL_Renderer *renderer = dynamic_cast<SDLGraphicsEngineRenderer *>(mRenderer)->GetRenderer();

    // Render each of the character(s)
    for (GameObject *entity : m_gameObjects)
    {
        entity->Render(renderer);
    }

    // Flip the buffer to render
    mRenderer->RenderPresent();
}

// Loops forever!
void Engine::MainGameLoop()
{
    // Main loop flag
    // If this is m_quit = 'true' then the program terminates.
    // While application is running
    while (!m_quit)
    {
        Uint32 start = SDL_GetTicks();

        Update();
        Render();

        // Cap FPS
        Uint32 duration = SDL_GetTicks() - start;
        if (duration < SCREEN_TICKS_PER_FRAME)
        {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - duration);
        }
    }
    // Disable text input
    SDL_StopTextInput();
}

void Engine::Start()
{
    // Report which subsystems are being initialized
    if (mRenderer != nullptr)
    {
        std::cout << "Initializing Graphics Subsystem\n";
    }
    else
    {
        std::cout << "No Graphics Subsystem initialized\n";
    }

    // Create game object for the character
    GameObject *character = new GameObject;
    // Create components for the character
    // A main character in this game has controller, transform and sprite as components
    ControllerComponent *controller = new ControllerComponent(&m_quit);
    // initial position
    TransformComponent *transform = new TransformComponent(128, 508, controller);
    SpriteComponent *sprite = new SpriteComponent(transform);

    // Load an image for our character
    SDL_Renderer *renderer = dynamic_cast<SDLGraphicsEngineRenderer *>(mRenderer)->GetRenderer();
    sprite->LoadImage("./images/sprite.bmp", renderer);

    // Wrap components into a game object
    // The order of addition matters as it determines update sequence
    character->AddComponent(controller);
    character->AddComponent(transform);
    character->AddComponent(sprite);
    m_gameObjects.push_back(character);

    // Setup our TileMap
    // This tile map is 20x11 in our game
    // It is using a 'reference' tile map with 8x8 tiles
    // that are each 64x64 pixels.
    GameObject *map = new GameObject;
    TileMapComponent *myTileMap = new TileMapComponent("./images/Tiles1.bmp", 8, 8, 64, 64, 20, 11, renderer);
    // Generate a a simple tile map
    myTileMap->GenerateSimpleMap();
    // Print out the map to the console
    // so we can see what was created.
    myTileMap->PrintMap();
    // Encapsulate TileMap in a container
    map->AddComponent(myTileMap);
    m_gameObjects.push_back(map);
}

void Engine::Shutdown()
{
    for (GameObject *entity : m_gameObjects)
    {
        delete entity;
    }
    // Shut down our Tile Systems
    if (nullptr != mRenderer)
    {
        delete mRenderer;
    }
}

void Engine::InitializeGraphicsSubSystem()
{
    // Setup our Renderer
    mRenderer = new SDLGraphicsEngineRenderer(1280, 720);
    if (nullptr == mRenderer)
    {
        exit(1); // Terminate program if renderer
                 // cannot be created.
                 // (Optional) TODO:   Could put an error
                 //                    messeage, or try to
                 //                    reinitialize the engine
                 //                    with a different render
    }
}
