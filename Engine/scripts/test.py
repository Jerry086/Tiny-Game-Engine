import mygameengine
def testembed():
    mygameengine.VariableManager.IncrementCounter("test embed", 1)
    print("value of testembed in python", mygameengine.VariableManager.GetCounter("test embed"))