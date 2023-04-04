#ifndef GAMEOBJECTMANAGER
#define GAMEOBJECTMANAGER

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "IGraphicsEngineRenderer.hpp"
#include "GameObject.hpp"

const int SCREEN_FPS = 30;
const float SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

/**
 * This class sets up the main game engine
 */
class GameObjectManager
{
public:
    /**
     * Constructor of Engine
     */
    Engine();
    /**
     * Destructor
     */
    ~Engine();
    /**
     * Per frame update
     */
    void Update();
    /**
     * Per frame render. Renders everything
     */
    void Render();
    /**
     * Main Game Loop that runs forever
     */
    void MainGameLoop();
    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Start' to launch the engine
     */
    void Start();
    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();

    /**
     * Request to startup the Graphics Subsystem
     */
    void InitializeGraphicsSubSystem();

private:
    // Engine Subsystem
    // Setup the Graphics Rendering Engine - render is unique
    IGraphicsEngineRenderer *mRenderer = nullptr;
    // Collection of game objects
    std::vector<GameObject *> m_gameObjects;
    // flag to quit a game
    bool m_quit = false;
};

#endif
