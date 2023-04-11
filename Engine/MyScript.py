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
# go = create_go('GO id', './definitions/test_npc.json')
# tilemap = create_go('Tilemap', './definitions/test_tilemap.json')
# go = mygameengine.GameObject("player id")
# controller_component = mygameengine.ControllerComponent()
# transform_component = mygameengine.TransformComponent(
#     mygameengine.Vec2(10, 10), mygameengine.Vec2(100, 100), controller_component
# )
# collision_component = mygameengine.CollisionComponent(
#     "player", transform_component, 75, 87
# )

# sprite_component = mygameengine.SpriteComponent(
#     "./sprites/pacman2.bmp", transform_component, 0, 0, 64, 64, 8, 4, 8
# )
# tilemap_component = mygameengine.TileMapComponent(
#     "./sprites/Tiles1.bmp", 8, 8, 64, 64, 20, 11
# )

# # healthbar_component = mygameengine.HealthBarComponent(
# #     './sprites/healthBar.bmp', transform_component, 100, 100, 105, 1074)

# go.AddComponent("1", controller_component)
# go.AddComponent("2", transform_component)
# go.AddComponent("3CollisionComponent", collision_component)
# go.AddComponent("4", sprite_component)
# go.AddComponent("5", tilemap_component)
# # go.AddComponent('5', healthbar_component)

# # game_objects = create_scene('./definitions/test_scene_def.json')

# wall = mygameengine.GameObject("wall id")
# behavior_component = mygameengine.BehaviorComponent()
# transform_component2 = mygameengine.TransformComponent(
#     mygameengine.Vec2(5, 5), mygameengine.Vec2(1000, 100), behavior_component
# )
# collision_component2 = mygameengine.CollisionComponent(
#     "wall", transform_component2, 64, 64
# )
# sprite_component2 = mygameengine.SpriteComponent(
#     "./sprites/Tiles1.bmp", transform_component2, 100, 100, 64, 64, 1, 8, 8
# )

# wall.AddComponent("0", behavior_component)
# wall.AddComponent("1", transform_component2)
# wall.AddComponent("3CollisionComponent", collision_component2)
# wall.AddComponent("4", sprite_component2)

# game_object_manager = mygameengine.GameObjectManager()
# game_object_manager.AddGameObject("player", go)
# game_object_manager.AddGameObject("wall", wall)


print("Setting up game loop")
while not controller_component.QuitProgram():
    SDL.clear()

    # for go in game_objects:
    #     go.Update()

    # for go in game_objects:
    #     go.Render()

    game_object_manager.Update()
    game_object_manager.Render()

    SDL.flip()
    SDL.delay(20)
