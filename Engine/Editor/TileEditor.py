from tkinter import messagebox
from mods import *

class MainApp(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self) #Inherits the main window from tkinnter
        self.saved = True #holds a value for whether or not  the tilemap has been saved
        self.title("Tile Basic")
        self.geometry("1280x720")
        self.tmap = TileMap(self, 125) #creates an object that holds the images, canvas objects, and paths for our tilemap
        self.ibox = ImageFrame(self) #creates the box that holds our tiles
        self.tbox = ToolFrame(self) #creates a box that holds our tools
        self.tbar = TopBar(self) #creates the window's topbar
        self.cframe = CanvasFrame(self, self.title)
        self.protocol("WM_DELETE_WINDOW", self.Quit) #changes what the window does when we click to close it
        # self.mainloop()
        while True:
            try:
                self.update()
            except tk.TclError:
                break

    def Quit(self):
        if self.saved:
            self.destroy() #destroy the window if everything is saved...
        else: #...otherwise, ask the user if he/she wants to save his/her work
            mbox = tk.messagebox.askquestion(title="Save File", 
                                             message="Some changes are unsaved! Would you like to save your progress?")
            if mbox=="no": #if no, end the program without saving
                self.destroy()
            else:
                self.tbar.fmenu.SaveProgress() #otherwise, save.

app = MainApp()
