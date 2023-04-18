import os
import sys
import importlib.util

# Load mygameengine.so dynamically
if getattr(sys, 'frozen', False):
    # Running in a bundled executable
    script_dir = sys._MEIPASS

    # Change the working directory for bundled executables
    # os.chdir(sys._MEIPASS)
else:
    # Running in a normal Python environment
    script_dir = os.path.dirname(os.path.abspath(__file__))

shared_lib_path = os.path.join(script_dir, 'mygameengine.so')

spec = importlib.util.spec_from_file_location('mygameengine', shared_lib_path)
mygameengine = importlib.util.module_from_spec(spec)
spec.loader.exec_module(mygameengine)

# import mygameengine

from def_parser import create_scene
import time

WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 768

SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

game_object_manager = mygameengine.GameObjectManager()

game_objects = create_scene("./definitions/scenes/scene_def_pacman.json")
# scene_def_path = os.path.join(script_dir, 'definitions', 'scenes', 'scene_def_pacman.json')
# game_objects = create_scene(scene_def_path)

for go_name, go in game_objects:
    game_object_manager.AddGameObject(go_name, go)

game_object_manager.StartUp()

print("Setting up game loop")
while not mygameengine.GameManager.IsQuit():
    SDL.clear()

    mygameengine.ServiceLocator.Update()
    mygameengine.ServiceLocator.Render()

    # game_object_manager.Update()
    # game_object_manager.Render()

    SDL.flip()
    SDL.delay(50)
game_object_manager.ShutDown()
# mygameengine.GameManager.ShowGameOverPopup()
SDL.ShutDown()
print("Python End of game loop")
