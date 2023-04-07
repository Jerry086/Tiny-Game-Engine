import tkinter as tk
from tkinter import filedialog
import json
def load_file():
    filepath = filedialog.askopenfilename(filetypes=(("JSON files", "*.json"), ("All files", "*.*")))
    print("Selected file:", filepath)
    if filepath:
        with open('data.json') as f:
            data = json.load(f)
            print(data)


root = tk.Tk()
root.geometry("800x600")
# Create a Frame for the left side of the window
left_frame = tk.Frame(root)
left_frame.pack(side="left", fill="y")

# Create a button to load a file in the left frame
load_button = tk.Button(left_frame, text="Load File",command=load_file)
load_button.pack()

# Create a Frame for the right side of the window
right_frame = tk.Frame(root)
right_frame.pack(side="right", fill="both", expand=True)

# Add widgets to the right frame
# ...

root.mainloop()



