import mygameengine

def collision_component_on_collision():
    other_name = mygameengine.VariableManager.GetString("pac_CollisionComponent_other_name")
    other_type = mygameengine.VariableManager.GetString("pac_CollisionComponent_other_type")
    print("collision with", other_name, other_type)
    mygameengine.GameObjectManager().GetGameObject("pac").m_enabled = False