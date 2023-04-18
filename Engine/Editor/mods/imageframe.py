# import def_parser
import tkinter as tk
import tkinter.filedialog
from tkinter import RIDGE, FLAT, NSEW
import os
from .filehandle import *
import json
import sys
# sys.path.insert(0,  os.path.abspath('../'))


class ImageFrame(tk.Frame):
    def __init__(self, parent):
        # print(  def_parser)
        tk.Frame.__init__(self, parent, height=210, width=180,
                          padx=0, pady=0, borderwidth=2, relief=RIDGE)
        self.parent = parent
        self.currentImagePath = ""
        self.currentImage = ""
        self.currentComponent = ""
        # make a scroll bar for the tilebox
        self.ybar = tk.Scrollbar(self, orient="vertical")
        # make a canvas for the scroll bar to scroll. this canvas holds the buttons
        self.imgcanv = ImageCanvas(self)
        self.ybar["command"] = self.imgcanv.yview
        self.ybar.grid(column=1, row=0, sticky="ns")
        # keeps frame from shrinking to the size of the objects it contains
        self.grid_propagate(False)
        # sets the position of the image frame
        self.grid(row=0, column=0, padx=0, pady=10, sticky="n")
        self.loader = LoaderFrame(self.parent, self)
        # Create and place the "Load File" button next to the frame
        # self.load_button = tk.Button(self, text="Load File", command=self.load_file)
        # self.load_button.grid(column=1, row=0, padx=90, pady=10, )

        # # Create and place the dropdown list
        # self.dropdown = tk.OptionMenu(self, tk.StringVar(), [])
        # self.dropdown.grid(column=0, row=0, padx=10, pady=10)


class LoaderFrame(tk.Frame):
    def __init__(self, parent, frameParent):
        tk.Frame.__init__(self, parent, height=210, width=180,
                          padx=0, pady=0, borderwidth=2, relief=RIDGE)
        self.parent = frameParent
        self.grid(row=1, column=0, padx=20, pady=10, sticky="n")

        # Create and place the "Load File" button next to the frame
        self.load_button = tk.Button(
            self, text="Load File", command=self.load_file)
        self.load_button.grid(column=2, row=0, padx=20, pady=10, )

        self.load_button = tk.Button(
            self, text="Create GameObject", command=self.createGameObject)
        self.load_button.grid(column=3, row=0, padx=20, pady=10, )

        self.label = tk.Label(self, text="Select an option: ")
        self.label.grid(row=0, column=0)

        # Create the component type dropdown
        self.component_var = tk.StringVar(self)
        # self.component_var["menuname"] = "MyMenu"
        self.comps = []
        self.compNames = []
        self.component_var.set("Select Component Type")
        self.dropdown = tk.OptionMenu(self, self.component_var, [])
        self.dropdown.grid(column=1, row=0, padx=10, pady=10)

    def on_component_change(self, *args):
        selected_component = self.component_var.get()
        print("Selected component:", selected_component)
        print(self.comps)
        print(self.parent.imgcanv.buttons)
        # self.parent.imgcanv.buttons.clear()
        for item in self.parent.imgcanv.buttons:
            item.destroy()
        #     print (item)

            self.parent.imgcanv.newbtnpos = (0, 0)
        for sc in self.comps:
            if (sc['name'] == selected_component):
                x, y, w, h, rowOffset, colOffset = None, None, None, None, None, None
                for arg in sc['restArgs']:
                    if arg["arg_name"] == 'w':
                        w = int(arg["value"])
                    elif arg["arg_name"] == 'h':
                        h = int(arg["value"])
                    elif arg["arg_name"] == 'rowOffset':
                        rowOffset = int(arg["value"])
                    elif arg["arg_name"] == 'colOffset':
                        colOffset = int(arg["value"])
                if w and h and rowOffset != None and colOffset != None:
                        x = int(w) * int(colOffset)
                        y = int(h) * int(rowOffset)
                abs_path = os.path.abspath("../" + sc["value"])
                print('abs path', abs_path)
                print('x', x, 'y', y, 'w', w, 'h', h, 'rowOffset', rowOffset, 'colOffset', colOffset)
                self.parent.imgcanv.MakeButton((os.path.abspath("../" + sc["value"]),), x=x, y=y, w=w, h=h)

    def load_file(self):
        # Code to load JSON file and fill the dropdown list
        path = tk.filedialog.askopenfilename(title="Open Def File", filetypes=[
                                             ("Json File(.json)", ".json")])
        # print(str(path))
        self.jsonPath = path
        if (path):
            with open(path, "r") as file:
                data = json.load(file)
                components = data.get("components", [])
                for component in components:
                    if len(component['args']):
                        for arg in component['args']:
                            if arg["arg_type"] == "string" and ".bmp" in arg["value"]:
                                self.comps.append(
                                    {"name": component["component_type"], "value": arg["value"], "restArgs": component['args']})
                                if component["component_type"] not in self.compNames:
                                    self.compNames.append(
                                        component["component_type"])
                                # print(os.path.abspath(  arg["value"]))
                                # self.parent.imgcanv.MakeButton((os.path.abspath( "../"+  arg["value"]),))
                # Update the component type dropdown menu
                self.component_var.set("Select Component Type")
                component_menu = self.nametowidget(self.dropdown.menuname)
                component_menu.delete(0, tk.END)
                for option in self.compNames:
                    # print(option['name'])
                    component_menu.add_command(label=option, command=tk._setit(
                        self.component_var, option))
                component_menu.update()
                self.component_var.trace("w", self.on_component_change)

    def createGameObject(self):
        # pass
        playerGO = def_parser.create_go('Player', self.jsonPath)
        print(playerGO)
        fts = [("JSON File", ".json")]
        path = tk.filedialog.asksaveasfilename(title="Save game object",
                                               filetypes=fts, defaultextension=fts)


class ImageCanvas(tk.Canvas):
    def __init__(self, parent):
        tk.Canvas.__init__(self, parent)
        self.parent = parent  # holds access to the parent (ImageFrame)
        # set the width to allow 20 pixels of space for the scrollbar
        self["width"] = 160
        # set the height to allow 10 pixels of space for the bottom ridge
        self["height"] = 200
        self.buttons = []  # holds the UI buttons that represent each tile
        self.tilesize = 32
        self.lastDir = ''
        self.newbtnpos = (0, 0)
        # creates an enourmous scroll region for many amounts of tiles
        self["scrollregion"] = (0, 0, 0, 1000)
        self["yscrollcommand"] = self.parent.ybar.set
        self.grid()

    def OpenImage(self, x=None, y=None, w=None, h=None):
        if self.lastDir == '':
            # access user's home dir and go to the pictures folder
            self.lastDir = os.path.expanduser("~") + "/Pictures"
        # Store path from savefile dialog to variable
        paths = tk.filedialog.askopenfilenames(title="Open Image", initialdir=self.lastDir,
                                               filetypes=[("Images Files", ".png .jpg .jpeg .bmp")])
        self.lastDir = paths  # path to last opened file
        self.MakeButton(paths, x=x, y=y, w=w, h=h)

    def MakeButton(self, paths, x=None, y=None, w=None, h=None):
        # print(paths)
        for p in paths:  # for each file in the selected files
            # add a corresponding button
            self.buttons.append(TileButton(self, p, self.newbtnpos, x=x, y=y, w=w, h=h))
            # make the next button over from the last
            self.newbtnpos = (
                self.newbtnpos[0] + self.tilesize+2, self.newbtnpos[1])
            if self.newbtnpos[0] > 160 - self.tilesize:
                # every 4 buttons, go a line down
                self.newbtnpos = (0, self.newbtnpos[1] + self.tilesize+2)

    def selectTile(self, i):
        # sets the path to the currently selected image
        self.parent.currentImagePath = str(self.buttons[i].path)
        # sets the currently selected image
        self.parent.currentImage = self.buttons[i].tile.image
        for cmp in self.parent.loader.comps:
            # print(cmp['value'])
            if (os.path.abspath("../" + cmp['value']) == str(self.buttons[i].path)):
                self.parent.currentComponent = cmp['name']


class TileButton(tk.Button):
    def __init__(self, parent, path, plc, x=None, y=None, w=None, h=None):
        tk.Button.__init__(self, parent, relief=FLAT)
        self.parent = parent
        self.plc = plc

        self.path = path
        # create a button object on the imagecanvas scroll region.
        self.parent.create_window(
            self.plc[0], self.plc[1], window=self, anchor=tk.NW)
        # load the tile our button will represent
        print('tile button init path', path)
        self.tile = Tile(self.path, self.parent.tilesize, x=x, y=y, w=w, h=h)
        # make the button display the image of the tile it represents
        self["image"] = self.tile.image
        self["command"] = lambda i = len(parent.buttons): parent.selectTile(
            i)  # make button's tile the selected one
