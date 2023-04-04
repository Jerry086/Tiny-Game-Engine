import mygameengine
from def_parser import create_components, create_go
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

go = create_go('GO id', './definitions/test_npc.json')

buttons = [False, False, False, False]


print("Setting up game loop")
while True:
    start_time = time.monotonic()
    SDL.clear()
    go.Update()
    go.Render()
    SDL.flip()
    SDL.delay(20)
