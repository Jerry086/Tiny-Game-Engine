import tkinter as tk
import tkinter.filedialog
from tkinter import RIDGE, FLAT, NSEW
import os
from .filehandle import *

class ImageFrame(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent, height=210, width=180, padx=0, pady=0, borderwidth=2, relief=RIDGE)
        self.parent = parent
        self.currentImagePath = ""
        self.currentImage = ""
        self.ybar = tk.Scrollbar(self, orient = "vertical") #make a scroll bar for the tilebox
        self.imgcanv = ImageCanvas(self) #make a canvas for the scroll bar to scroll. this canvas holds the buttons
        self.ybar["command"] = self.imgcanv.yview
        self.ybar.grid(column=1,row=0,sticky="ns")
        self.grid_propagate(False) #keeps frame from shrinking to the size of the objects it contains
        self.grid(row=0, column=0, padx=0, pady=10, sticky = "n") #sets the position of the image frame
            # Create a new frame for the button and place it in the bottom row
        # btn_frame = tk.Frame(parent)
        # btn_frame.grid(row=1, column=0, pady=10)

        # # Create the "Add Image" button and add it to the button frame
        # add_btn = tk.Button(btn_frame, text="Add Image")
        # add_btn.pack()

class ImageCanvas(tk.Canvas):
    def __init__(self, parent):
        tk.Canvas.__init__(self, parent)
        self.parent = parent #holds access to the parent (ImageFrame)
        self["width"] = 160 #set the width to allow 20 pixels of space for the scrollbar
        self["height"] = 200 #set the height to allow 10 pixels of space for the bottom ridge
        self.buttons = [] #holds the UI buttons that represent each tile
        self.tilesize = 32
        self.lastDir = ''
        self.newbtnpos = (0, 0)
        self["scrollregion"] = (0,0,0,1000) #creates an enourmous scroll region for many amounts of tiles
        self["yscrollcommand"] = self.parent.ybar.set
        self.grid()

    def OpenImage(self):
        if self.lastDir == '':
            self.lastDir = os.path.expanduser("~") + "/Pictures"#access user's home dir and go to the pictures folder
        #Store path from savefile dialog to variable
        paths = tk.filedialog.askopenfilenames(title = "Open Image", initialdir = self.lastDir,
                                                      filetypes = [("Images Files", ".png .jpg .jpeg .bmp")])
        self.lastDir = paths #path to last opened file
        self.MakeButton(paths)

    def MakeButton(self, paths):
        for p in paths: #for each file in the selected files
            self.buttons.append(TileButton(self, p, self.newbtnpos)) #add a corresponding button
            self.newbtnpos = (self.newbtnpos[0] + self.tilesize+2, self.newbtnpos[1]) #make the next button over from the last
            if self.newbtnpos[0] > 160 - self.tilesize:
                self.newbtnpos = (0, self.newbtnpos[1] + self.tilesize+2) #every 4 buttons, go a line down

    def selectTile(self, i):
        self.parent.currentImagePath = str(self.buttons[i].path) #sets the path to the currently selected image
        self.parent.currentImage = self.buttons[i].tile.image #sets the currently selected image
        
class TileButton(tk.Button):
    def __init__(self, parent, path, plc):
        tk.Button.__init__(self, parent, relief=FLAT)
        self.parent = parent
        self.plc = plc
      
        self.path = path
        self.parent.create_window(self.plc[0], self.plc[1], window = self, anchor = tk.NW) #create a button object on the imagecanvas scroll region. 
        self.tile = Tile(self.path, self.parent.tilesize) #load the tile our button will represent
        self["image"] = self.tile.image #make the button display the image of the tile it represents
        self["command"] = lambda i = len(parent.buttons): parent.selectTile(i) #make button's tile the selected one
