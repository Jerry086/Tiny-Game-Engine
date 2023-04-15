import mygameengine
from def_parser import create_scene
import time

WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

game_object_manager = mygameengine.GameObjectManager()
game_object_manager.StartUp()

game_objects = create_scene("./definitions/test_scene_def.json")

for go_name, go in game_objects:
    game_object_manager.AddGameObject(go_name, go)

print("Setting up game loop")
while not mygameengine.GameManager.IsQuit() and not mygameengine.GameManager.IsGameOver():
    SDL.clear()

    mygameengine.ServiceLocator.Update()

    game_object_manager.Update()
    game_object_manager.Render()

    SDL.flip()
    SDL.delay(20)
game_object_manager.ShutDown()
# mygameengine.GameManager.ShowGameOverPopup()
SDL.ShutDown()
print("Python End of game loop")
