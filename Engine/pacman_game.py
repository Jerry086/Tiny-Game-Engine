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

import sys
sys.path.append('./Assets/utils')
from def_parser import create_scene
import time

WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 768
SCREEN_FPS = 30
SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS

SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

game_object_manager = mygameengine.GameObjectManager()

scene_def_path = "./Assets/definitions/scenes/scene_def_pacman.json"
if len(sys.argv) > 1:
    scene_def_path = sys.argv[1]
game_objects = create_scene(scene_def_path)

for go_name, go in game_objects:
    game_object_manager.AddGameObject(go_name, go)

game_object_manager.StartUp()

print("Setting up game loop")
while not mygameengine.GameManager.IsQuit():
    start_time = time.time()

    SDL.clear()

    mygameengine.ServiceLocator.Update()
    mygameengine.ServiceLocator.Render()

    # game_object_manager.Update()
    # game_object_manager.Render()

    SDL.flip()

    end_time = time.time()
    dt = end_time - start_time
    if dt < SCREEN_TICKS_PER_FRAME:
        SDL.delay(int((SCREEN_TICKS_PER_FRAME - dt)))

game_object_manager.ShutDown()
# mygameengine.GameManager.ShowGameOverPopup()
SDL.ShutDown()
print("Python End of game loop")
