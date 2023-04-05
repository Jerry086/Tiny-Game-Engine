import mygameengine
from def_parser import create_components, create_go, create_scene
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

# go = create_go('GO id', './definitions/test_npc.json')
# tilemap = create_go('Tilemap', './definitions/test_tilemap.json')
go = mygameengine.GameObject('player id')
controller_component = mygameengine.ControllerComponent()
transform_component = mygameengine.TransformComponent(
    mygameengine.Vec2(10, 10), mygameengine.Vec2(100, 100), controller_component)
collision_component = mygameengine.CollisionComponent(
    "player", transform_component, 75, 87)

sprite_component = mygameengine.SpriteComponent(
    './sprites/sprite.bmp', transform_component, 100, 100, 75, 87, 27, 7, 4)
tilemap_component = mygameengine.TileMapComponent(
    './sprites/Tiles1.bmp', 8, 8, 64, 64, 20, 11)

# healthbar_component = mygameengine.HealthBarComponent(
#     './sprites/healthBar.bmp', transform_component, 100, 100, 105, 1074)

go.AddComponent('1', controller_component)
go.AddComponent('2', transform_component)
go.AddComponent('3CollisionComponent', collision_component)
go.AddComponent('4', sprite_component)
go.AddComponent('5', tilemap_component)
# go.AddComponent('5', healthbar_component)

game_objects = create_scene('./definitions/test_scene_def.json')

wall = mygameengine.GameObject('wall id')
transform_component2 = mygameengine.TransformComponent(
    mygameengine.Vec2(1000, 100))
collision_component2 = mygameengine.CollisionComponent(
    "wall", transform_component2, 64, 64)
sprite_component2 = mygameengine.SpriteComponent(
    './sprites/Tiles1.bmp', transform_component2, 100, 100, 64, 64, 1, 8, 8)

wall.AddComponent('1', transform_component2)
wall.AddComponent('3CollisionComponent', collision_component2)
wall.AddComponent('4', sprite_component2)

game_object_manager = mygameengine.GameObjectManager()
game_object_manager.AddGameObject('player', go)
game_object_manager.AddGameObject('wall', wall)


print("Setting up game loop")
while True:
    SDL.clear()
    # go.Update()
    # tilemap.Update()
    # go.Render()
    # tilemap.Render()

    for go in game_objects:
        go.Update()
    
    for go in game_objects:
        go.Render()
        
    game_object_manager.Update()
    game_object_manager.Render()
    SDL.flip()
    SDL.delay(20)
