import mygameengine
from def_parser import create_components, create_go, create_scene
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

go = create_go('player', './definitions/test_player.json')
controller_component = go.GetComponent('0')
tilemap = create_go('Tilemap', './definitions/test_tilemap.json')

# game_objects = create_scene('./definitions/test_scene_def.json')

wall = create_go('wall', './definitions/test_randommove.json')

# wall = mygameengine.GameObject('wall id')
# behavior_component = mygameengine.BehaviorComponent()
# transform_component2 = mygameengine.TransformComponent(
#     mygameengine.Vec2(5, 5), mygameengine.Vec2(1000, 100), behavior_component)
# collision_component2 = mygameengine.CollisionComponent(
#     "wall", transform_component2, 64, 64)
# sprite_component2 = mygameengine.SpriteComponent(
#     './sprites/Tiles1.bmp', transform_component2, 100, 100, 64, 64, 1, 8, 8)

# wall.AddComponent('0', behavior_component)
# wall.AddComponent('1', transform_component2)
# wall.AddComponent('3CollisionComponent', collision_component2)
# wall.AddComponent('4', sprite_component2)

game_object_manager = mygameengine.GameObjectManager()
game_object_manager.AddGameObject('player', go)
game_object_manager.AddGameObject('wall', wall)


print("Setting up game loop")
while not controller_component.QuitProgram():
    SDL.clear()
    # go.Update()
    # tilemap.Update()
    # go.Render()
    # tilemap.Render()

    # for go in game_objects:
    #     go.Update()
    
    # for go in game_objects:
    #     go.Render()
        
    game_object_manager.Update()
    game_object_manager.Render()
    SDL.flip()
    SDL.delay(20)