class GameStateManager:
    def __init__(self):
        self.states = []
        self.current_state = None

    def create_state(self, state):
        new_state = state()
        self.states.append(new_state)

    def set_state(self, state_name):
        for state in self.states:
            if state.name == state_name:
                self.current_state = state

    def update(self):
        if self.current_state is not None:
            pass# self.current_state.update()
