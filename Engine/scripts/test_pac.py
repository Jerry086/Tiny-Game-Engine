import mygameengine
def collision_component_update():
    mygameengine.VariableManager.IncrementCounter("test pac", 1)
    print("value of testembed in python", mygameengine.VariableManager.GetCounter("test pac"))