import mygameengine
import time
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720
BALL_SPEED = 1.0
dt = 0.0
BALL_WIDTH = 15
BALL_HEIGHT = 15

PADDLE_SPEED = 1.0
PADDLE_WIDTH = 10
PADDLE_HEIGHT = 100

SDL = mygameengine.SDLGraphicsProgram(WINDOW_WIDTH,WINDOW_HEIGHT)


ball = mygameengine.Ball(
    mygameengine.Vec2(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0),
    mygameengine.Vec2(BALL_SPEED, 0.0))

paddle_one = mygameengine.Paddle(
    mygameengine.Vec2(50.0, WINDOW_HEIGHT / 2.0),
    mygameengine.Vec2(0.0, 0.0))

paddle_two = mygameengine.Paddle(
    mygameengine.Vec2(WINDOW_WIDTH - 50.0, WINDOW_HEIGHT / 2.0),
    mygameengine.Vec2(0.0, 0.0))
score_one = 0
score_two = 0

go = mygameengine.GameObject('GO id')
controller_component = mygameengine.ControllerComponent()
transform_component = mygameengine.TransformComponent(mygameengine.Vec2(100,100), mygameengine.Vec2(0,0), controller_component)
sprite_component = mygameengine.SpriteComponent('./sprites/sprite.bmp', transform_component, 100, 100, 500, 500, 24)
go.AddComponent('python added transform component', transform_component)
go.AddComponent('python added sprite component', sprite_component)


buttons = [False,False,False,False]



print("Setting up game loop")
while True:
    start_time = time.monotonic()

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
            paddle_one.velocity.y = -PADDLE_SPEED
        elif (buttons[1]):
            paddle_one.velocity.y = PADDLE_SPEED
        else:
            paddle_one.velocity.y = 0.0

        if (buttons[2]):
            paddle_two.velocity.y = -PADDLE_SPEED
        elif (buttons[3]):
            paddle_two.velocity.y = PADDLE_SPEED
        else:
            paddle_two.velocity.y = 0.0
 
    paddle_one.Update(dt)
    paddle_two.Update(dt)

    ball.Update(dt)
    go.Update()

    contact1_pd = mygameengine.CheckPaddleCollision(ball, paddle_one)
    contact2_pd = mygameengine.CheckPaddleCollision(ball, paddle_two)

    contact1_wall = mygameengine.CheckWallCollision(ball)
     
    if ( contact1_pd.type != 0): #none
        ball.CollideWithPaddle(contact1_pd)
    elif (contact2_pd.type != 0):
            ball.CollideWithPaddle(contact2_pd)
    elif (contact1_wall.type != 0):
        ball.CollideWithWall(contact1_wall)
        if (contact1_wall.type == 4):
            score_two += 1
            # print(f"score for player 2: {score_two}")
        elif (contact1_wall.type == 5):
            score_one += 1
            # print(f"score for player 1: {score_one}")

    # SDL.clear()
    

    for i in range(0, WINDOW_HEIGHT):
        if (i % 5):
            SDL.DrawPoint(WINDOW_WIDTH // 2, i)

    ball.Draw()
    paddle_one.Draw()
    paddle_two.Draw()
    go.Render()
 
    SDL.drawRect(ball, paddle_one,paddle_two  )
    SDL.flip()

    stop_time = time.monotonic() 
    dt = (stop_time - start_time) * 1000  
    startTime = stop_time  
 


