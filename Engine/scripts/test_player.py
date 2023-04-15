import mygameengine
def update():
    mygameengine.VariableManager.IncrementCounter("test player", 1)
    print("value of test player in python", mygameengine.VariableManager.GetCounter("test player"))