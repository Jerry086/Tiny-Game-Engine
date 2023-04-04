import mygameengine
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720


SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH, WINDOW_HEIGHT)

go = mygameengine.GameObject('GO id')
controller_component = mygameengine.ControllerComponent()
transform_component = mygameengine.TransformComponent(
    mygameengine.Vec2(10, 10), mygameengine.Vec2(100, 100), controller_component)

sprite_component = mygameengine.SpriteComponent(
    './sprites/sprite.bmp', transform_component, 100, 100, 75, 87, 27)
tilemap_component = mygameengine.TileMapComponent(
    './sprites/Tiles1.bmp',8,8,64,64,20,11)

# healthbar_component = mygameengine.HealthBarComponent(
#     './sprites/healthBar.bmp', transform_component, 100, 100, 105, 1074)

go.AddComponent('1', controller_component)
go.AddComponent('2', transform_component)
go.AddComponent('3', sprite_component)
go.AddComponent('4', tilemap_component)
# go.AddComponent('5', healthbar_component)


buttons = [False, False, False, False]


print("Setting up game loop")
while True:
    start_time = time.monotonic()
    SDL.clear()
    go.Update()
    go.Render()
    SDL.flip()
    SDL.delay(20)
