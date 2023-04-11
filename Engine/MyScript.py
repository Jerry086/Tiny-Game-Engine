import mygameengine
from def_parser import create_components, create_go, create_scene
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

# player = create_go('player', './definitions/test_player.json')
# controller_component = player.GetComponent('0')
# tilemap = create_go('Tilemap', './definitions/test_tilemap.json')
# wall = create_go('wall', './definitions/test_randommove.json')


game_object_manager = mygameengine.GameObjectManager()
# game_object_manager.AddGameObject('player', player)
# game_object_manager.AddGameObject('wall', wall)

game_objects = create_scene('./definitions/test_scene_def.json')

for go_name, player in game_objects:
    game_object_manager.AddGameObject(go_name, player)

controller_component = game_object_manager.GetGameObject('player').GetComponent('0')


print("Setting up game loop")
while not controller_component.QuitProgram():
    SDL.clear()
        
    game_object_manager.Update()
    game_object_manager.Render()
    SDL.flip()
    SDL.delay(20)