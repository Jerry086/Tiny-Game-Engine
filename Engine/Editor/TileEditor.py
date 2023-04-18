from tkinter import messagebox
from mods import *

class MainApp(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self) #Inherits the main window from tkinnter
        self.saved = True #holds a value for whether or not  the tilemap has been saved
        self.title("Tile Basic")
        self.geometry("1280x720")
        self.tmap = TileMap(self, 20, 12) #creates an object that holds the images, canvas objects, and paths for our tilemap
        # self.loader = LoaderFrame(self)
        self.ibox = ImageFrame(self) #creates the box that holds our tiles
        self.tbox = ToolFrame(self) #creates a box that holds our tools
        self.tbar = TopBar(self) #creates the window's topbar
        self.cframe = CanvasFrame(self, self.title) # tilemap edit area
        self.protocol("WM_DELETE_WINDOW", self.Quit) #changes what the window does when we click to close it
        self.mainloop()
        # while True:
        #     try:
        #         self.update()
        #     except tk.TclError:
        #         break

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
# import time, os, sys, subprocess

# PY2 = sys.version_info[0] == 2

# class Reloader(object):

#     RELOADING_CODE = 3
#     def start_process(self):
#         """Spawn a new Python interpreter with the same arguments as this one,
#         but running the reloader thread.
#         """
#         while True:
#             print("starting Tkinter application...")

#             args = [sys.executable] + sys.argv
#             env = os.environ.copy()
#             env['TKINTER_MAIN'] = 'true'

#             # a weird bug on windows. sometimes unicode strings end up in the
#             # environment and subprocess.call does not like this, encode them
#             # to latin1 and continue.
#             if os.name == 'nt' and PY2:
#                 for key, value in env.iteritems():
#                     if isinstance(value, unicode):
#                         env[key] = value.encode('iso-8859-1')

#             exit_code = subprocess.call(args, env=env,
#                                         close_fds=False)
#             if exit_code != self.RELOADING_CODE:
#                 return exit_code

#     def trigger_reload(self):
#         self.log_reload()
#         sys.exit(self.RELOADING_CODE)

#     def log_reload(self):
#         print("reloading...")

# def run_with_reloader(root, *hotkeys):
#     """Run the given application in an independent python interpreter."""
#     import signal
#     signal.signal(signal.SIGTERM, lambda *args: sys.exit(0))
#     reloader = Reloader()
#     try:
#         if os.environ.get('TKINTER_MAIN') == 'true':

#             for hotkey in hotkeys:
#                 root.bind_all(hotkey, lambda event: reloader.trigger_reload())
                
#             if os.name == 'nt':
#                 root.wm_state("iconic")
#                 root.wm_state("zoomed")

#             root.mainloop()
#         else:
#             sys.exit(reloader.start_process())
#     except KeyboardInterrupt:
#         pass

# if __name__ == "__main__":

#     run_with_reloader(MainApp(), "<Control-R>", "<Control-r>")