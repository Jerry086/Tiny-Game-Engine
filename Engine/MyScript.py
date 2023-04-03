import mygameengine
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH,WINDOW_HEIGHT)
go = mygameengine.GameObject('GO id')
controller_component = mygameengine.ControllerComponent()
transform_component = mygameengine.TransformComponent(mygameengine.Vec2(100,100), mygameengine.Vec2(0,0), controller_component)
sprite_component = mygameengine.SpriteComponent('./sprites/sprite.bmp', transform_component, 100, 100, 500, 500, 24)
go.AddComponent('python added transform component', transform_component)
go.AddComponent('python added sprite component', sprite_component)


buttons = [False,False,False,False]

FPS = 60
FRAME_TIME = 1.0 / FPS
lastTime = time.monotonic()

print("Setting up game loop")
while True:
    currentTime = time.monotonic()
    elapsedTime = currentTime - lastTime 

    SDL.clear()

    action = SDL.getKeyAction()

    if action == "exit":
        break

    if (action != "exit" and  action != "empty"):
        acSplit = action.split(",")
        if (len(acSplit) != 3):
            continue

        if (acSplit[2] == '0'):
            if (acSplit[0] == '1' and acSplit[1] == 'up'):
                buttons[0] = True

            elif (acSplit[0] == '1' and acSplit[1] == 'down'):
                buttons[1] = True
            elif (acSplit[0] == '2' and acSplit[1] == 'up'):
                buttons[2] = True
            elif (acSplit[0] == '2' and acSplit[1] == 'down'):
                buttons[3] = True
        elif (acSplit[2] == '1'):
            if (acSplit[0] == '1' and acSplit[1] == 'up'):
                buttons[0] = False
            elif (acSplit[0] == '1' and acSplit[1] == 'down'):
                buttons[1] = False

            elif (acSplit[0] == '2' and acSplit[1] == 'up'):
                buttons[2] = False
            elif (acSplit[0] == '2' and acSplit[1] == 'down'):
                buttons[3] = False

        if (buttons[0]):
            pass
        elif (buttons[1]):
            pass
        else:
            pass
        if (buttons[2]):
            pass
        elif (buttons[3]):
            pass
        else:
            pass

    go.Update()
    go.Render()
    SDL.flip()

    if elapsedTime < FRAME_TIME:
        time.sleep(FRAME_TIME - elapsedTime)
    lastTime = currentTime

 





