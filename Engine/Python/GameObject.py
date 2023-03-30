#!/usr/bin/env python3

import mygameengine


class GameObject:
    def __init__(self, x, y, w, h) -> None:
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.components = []
        return

    def StartUp(self):
        return

    def Shutdown(self):
        return

    def Update(self):
        return

    def Render(self):
        CPP_SDLRenderWrapper(textureid, screen_x, screen_y, w, h)
        return
