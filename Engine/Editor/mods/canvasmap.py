from textwrap import fill
import tkinter as tk
from tkinter import RIDGE, messagebox


# Frame is created on the window.  Frame then creates canvas in it
class CanvasFrame(tk.Frame):
    def __init__(self, parent, title):
        tk.Frame.__init__(self, parent)
        # allows access to the canvas frame's parent (main window)
        self.parent = parent
        # the width of the canvas...
        self.w = (self.parent.winfo_screenwidth() - 170) * 0.75
        # ...is 75% of the available screen space
        self.h = (self.parent.winfo_screenheight()) * 0.75
        self["relief"] = RIDGE  # creates a raised area around the canvas frame
        self["width"] = self.w
        self["height"] = self.h
        # print(self.w)
        # print(self.h)
        self["borderwidth"] = 5
        # # make a vertical scrollbar
        self.ybar = tk.Scrollbar(self, orient="vertical")
        # # make a horizontal scrollbar
        self.xbar = tk.Scrollbar(self, orient="horizontal")

        # create the grid-map that will hold the tiles and pass the title argument to it
        self.cmap = CanvasMap(self, title)

        # # set the scrollbar to change the "y" area seen on canvas
        # self.ybar["command"] = self.cmap.yview
        # # set the scrollbar to change the "x" area seen on canvas
        # self.xbar["command"] = self.cmap.xview
        # # make scrollbar span the distance of the canvas frame
        self.ybar.grid(column=1, row=0, sticky="ns")
        # # make scrollbar span the distance of the canvas frame
        self.xbar.grid(column=0, row=1, sticky="ew")

        # sets the padding region to 10% of the available space left.
        self.grid(row=0, column=1, padx=(self.parent.winfo_screenwidth() - 170) * 0.1,
                  pady=20, rowspan=2)  # Adding rowspan=2 allows the canvas to take up two rows


class CanvasMap(tk.Canvas):
    def __init__(self, parent, title):
        tk.Canvas.__init__(self, parent)
        # allows access to the canva's parent (canvas frame)
        self.parent = parent
        self.w = self.parent.w  # sets width and height of canvas to that of canvas frame
        self.h = self.parent.h
        self.title = title
        self["bg"] = "#2e2e2e"  # makes a dark grey color
        # sets size of percivable area of canvas to the parent frame's size
        # self["width"] = self.w
        # self["height"] = self.h

        self["width"] = 640
        self["height"] = 384

        self.maxTile = 1500
        # gives y scrolling autority to the y scrollbar
        # self["yscrollcommand"] = self.parent.ybar.set
        # gives x scrolling autority to the x scrollbar
        # self["xscrollcommand"] = self.parent.xbar.set
        # makes a large scrolling area of canvas
        self["scrollregion"] = (0, 0, 1500, 1500)
        self.xview_moveto("0.0")  # set x scroll to left of canvas
        self.yview_moveto("0.0")  # set y scroll to top of canvas
        self.tsize = 32
        self.bind("<Button-1>", self.selectTile)
        self.bind("<B1-Motion>", self.selectTile)
        self.bind("<ButtonRelease-1>", self.boxSelect)
        # create a list of lines spanning the canvas
        # add extra line so we don't miss a column
        for i in range(int(self.maxTile / self.tsize) + 1):
            self.create_line(i * self.tsize, 0, i * self.tsize,
                             self.maxTile, fill="red")  # draw vert line
        # add extra line so we don't miss a row
        for i in range(int(self.maxTile / self.tsize) + 1):
            self.create_line(0, i * self.tsize, self.maxTile, i *
                             self.tsize, fill="red")  # draw horiz line
        self.grid(column=0, row=0)  # puts the canvas on the canvas frame

    def selectTile(self, event):
        self.parent.parent.saved = False
        # the position of the left side of the horizontal scrollbar
        a = self.parent.xbar.get()[0]
        # the position of the bottom side of the vertical scrollbar
        b = self.parent.ybar.get()[0]
        # changes the clicked position on the canvas to a position on the map as a whole
        # finds the number of the tile that our click falls inside
        self.tilepos = (int((a * self.maxTile + event.x) / self.tsize),
                        int((b * self.maxTile + event.y) / self.tsize))

        self.setTile()

    def setTile(self):
        # print(self.parent.parent.ibox.loader.comps)
        # print(self.parent.parent.ibox.currentComponent)
        tm = self.parent.parent.tmap  # easy reference to the entire tilemap array
        if self.parent.parent.tbox.tool == "click":
            # easy reference to the current selected image
            img = self.parent.parent.ibox.currentImage
            # path = self.parent.parent.ibox.currentImagePath
            path = self.parent.parent.ibox.currentJsonPath
            cmpType = self.parent.parent.ibox.currentComponent
            # if len(img) == 0:
            #     return messagebox.showwarning(title="Error",message="Please select image first")
            # if a tile is already in the position we clicked
            if tm.canvasarray[self.tilepos[1]][self.tilepos[0]] != " ":
                # ...delete it
                self.delete(tm.canvasarray[self.tilepos[1]][self.tilepos[0]])
            # draw the selected tile on the canvas at the clicked position
            canimg = self.create_image(
                self.tilepos[0] * self.tsize, self.tilepos[1] * self.tsize, image=img, anchor=tk.NW)
            tm.tilearray[self.tilepos[1]][self.tilepos[0]] = path
            tm.canvasarray[self.tilepos[1]][self.tilepos[0]] = canimg
            tm.componentNameArray[self.tilepos[1]][self.tilepos[0]] = cmpType

            # ...and a canvas compatible image to another array.
            # print (س)

        if self.parent.parent.tbox.tool == "erase":
            self.delete(tm.canvasarray[self.tilepos[1]]
                        [self.tilepos[0]])  # erase tile
            # forget tile from canvas array
            tm.canvasarray[self.tilepos[1]][self.tilepos[0]] = ' '
            # remove tile from tilemap
            tm.tilearray[self.tilepos[1]][self.tilepos[0]] = ' '
            tm.componentNameArray[self.tilepos[1]][self.tilepos[0]] = ' '

        if self.parent.parent.tbox.tool == "boxselect":
            # if there is not a selection box being drawn...
            if self.parent.parent.tbox.boxstart == []:
                # ...hold the top corner of a new one
                self.parent.parent.tbox.boxstart = [
                    self.tilepos[0], self.tilepos[1]]
            else:
                try:
                    self.delete(self.rect)  # delete the selection box
                except:
                    pass
                # draws a selection rectangle that will be filled with tiles
                self.rect = self.create_rectangle(self.parent.parent.tbox.boxstart[0] * self.tsize, self.parent.parent.tbox.boxstart[1]
                                                  * self.tsize, self.tilepos[0] * self.tsize, self.tilepos[1] * self.tsize, dash=(5, 5), outline="black")

        self.title('NEU-TileMap Editor (column: ' + str(self.tilepos[0]+1) +
                   ', row: ' + str(self.tilepos[1]+1) + ')')

    def boxSelect(self, event):
        if self.parent.parent.tbox.tool == "boxselect":
            # easy reference to the starting corner of the selection box
            bxst = self.parent.parent.tbox.boxstart
            self.delete(self.rect)
            # loop through all possible positions inside the selection box
            for i in range(abs(bxst[0] - self.tilepos[0])):
                for j in range(abs(bxst[1] - self.tilepos[1])):
                    # make sure that the interior of the selection box is being filled
                    if bxst[0] > self.tilepos[0]:
                        if bxst[1] > self.tilepos[1]:
                            # place a tile at each position
                            self.fillBox(
                                i, j, self.tilepos[0], self.tilepos[1])
                        if bxst[1] < self.tilepos[1]:
                            self.fillBox(i, j, self.tilepos[0], bxst[1])
                    if bxst[0] < self.tilepos[0]:
                        if bxst[1] < self.tilepos[1]:
                            self.fillBox(i, j, bxst[0], bxst[1])
                        if bxst[1] > self.tilepos[1]:
                            self.fillBox(i, j, bxst[0], self.tilepos[1])
            # clear the start position of the starting corner of selection box
            self.parent.parent.tbox.boxstart = []

    # this function creates one tile at a particular position within the selection box
    def fillBox(self, i, j, pos1, pos2):
        tm = self.parent.parent.tmap  # easy reference to the entire tilemap array
        # easy reference to the current selected image
        img = self.parent.parent.ibox.currentImage
        # path = self.parent.parent.ibox.currentImagePath  # find the image location
        path = self.parent.parent.ibox.currentJsonPath  # find the image location
        # if a tile is already in the specified position
        if tm.canvasarray[j + pos2][i + pos1] != " ":
            self.delete(tm.canvasarray[j + pos2][i + pos1])  # erase tile
        # forget tile from canvas array
        tm.canvasarray[j + pos2][i + pos1] = ' '
        tm.tilearray[j + pos2][i + pos1] = ' '  # remove tile from tilemap
        # draw a tile at the specified position on the canvas
        canimg = self.create_image(
            (i + pos1) * self.tsize, (j + pos2) * self.tsize, image=img, anchor=tk.NW)
        # put the tile in the tile array and canvas array
        self.parent.parent.tmap.tilearray[j + pos2][i + pos1] = path
        self.parent.parent.tmap.canvasarray[j + pos2][i + pos1] = canimg
        self.parent.parent.tmap.componentNameArray[j + pos2][i + pos1] = self.parent.parent.ibox.currentComponent
