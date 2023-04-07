import mygameengine
from def_parser import create_components, create_go, create_scene
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

# go = create_go('GO id', './definitions/test_npc.json')
# tilemap = create_go('Tilemap', './definitions/test_tilemap.json')

game_objects = create_scene('./definitions/test_scene_def.json')

buttons = [False, False, False, False]


print("Setting up game loop")
while True:
    start_time = time.monotonic()
    SDL.clear()
    # go.Update()
    # tilemap.Update()
    # go.Render()
    # tilemap.Render()

    for go in game_objects:
        go.Update()
    
    for go in game_objects:
        go.Render()
        
    SDL.flip()
    SDL.delay(20)
