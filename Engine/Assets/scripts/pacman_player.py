import mygameengine

def game_object_update():
    pass


def collision_component_on_collision():
    other_name = mygameengine.VariableManager.GetDict("player_CollisionComponent_other_name")
    other_name = other_name.replace("_CollisionComponent", "")
    other_type = mygameengine.VariableManager.GetDict("player_CollisionComponent_other_type")
    if "interactable" in other_type:
        mygameengine.GameObjectManager().GetGameObject(other_name).m_enabled = False
    elif "enemy" in other_type:
        mygameengine.VariableManager.SetBool("isPacmanGameOver", True)