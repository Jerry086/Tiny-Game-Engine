import mygameengine
from def_parser import create_scene
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

#TODO: python collision object type enum as list


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

game_object_manager = mygameengine.GameObjectManager()

game_objects = create_scene('./definitions/test_scene_def.json')

# tile1 = mygameengine.GameObject('tile1')
# tile_transform = mygameengine.TransformComponent(mygameengine.Vec2(200, 200))
# tile_sprite = mygameengine.SpriteComponent('./sprites/Tiles1.bmp', tile_transform, 100, 100, 75, 87, 27, 7, 4)
# tile1.AddComponent('0', tile_transform)
# tile1.AddComponent('1', tile_sprite)
# game_objects = []
# game_objects.append(('tile1', tile1))

for go_name, player in game_objects:
    game_object_manager.AddGameObject(go_name, player)

# TODO Hackyyyy
controller_component = game_object_manager.GetGameObject('player').GetComponent('0')

# TODO remove, test
counter = game_object_manager.GetGameObject('player').GetComponent('4')
counter.SetCounter('test counter', 0)


print("Setting up game loop")
while not controller_component.QuitProgram():
    SDL.clear()

    game_object_manager.Update()
    game_object_manager.Render()

    SDL.flip()
    SDL.delay(20)