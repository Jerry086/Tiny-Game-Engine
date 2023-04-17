import mygameengine

def game_object_update():
    pass


def collision_component_on_collision():
    other_name = mygameengine.VariableManager.GetDict("player_CollisionComponent_other_name")
    print("Collision with: ", other_name)