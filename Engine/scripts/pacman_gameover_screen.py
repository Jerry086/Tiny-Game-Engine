import mygameengine

this_go, sprite_comp = None, None
def game_object_update():
    global this_go, sprite_comp
    isGameOver = mygameengine.VariableManager.GetBool('isPacmanGameOver')
    # if not this_go:
    #     this_go = mygameengine.GameObjectManager.GetGameObject('pacman_gameover_screen')
    # if this_go and not sprite_comp:
    #     sprite_comp = this_go.GetComponent('pacman_gameover_screen_SpriteComponent')
    # if sprite_comp:
    #     sprite_comp.m_enabled = isGameOver
    print('pacman_gameover_screen.py: game_object_update()', 'isGameOver =', isGameOver, 'this_go', this_go, 'sprite_comp =', sprite_comp)