import mygameengine
from def_parser import create_scene
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

#TODO: python collision object type enum as list


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

game_object_manager = mygameengine.GameObjectManager()

game_objects = create_scene('./definitions/test_scene_def.json')

for go_name, player in game_objects:
    game_object_manager.AddGameObject(go_name, player)

# TODO Hackyyyy
controller_component = game_object_manager.GetGameObject('player').GetComponent('0')


print("Setting up game loop")
while not controller_component.QuitProgram():
    SDL.clear()
        
    game_object_manager.Update()
    game_object_manager.Render()
    SDL.flip()
    SDL.delay(20)