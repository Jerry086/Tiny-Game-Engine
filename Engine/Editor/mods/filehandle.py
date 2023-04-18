import os
import PIL.ImageTk
import PIL.Image
from tkinter import NW, messagebox
import json


class Tile():  # class structure to hold images
    def __init__(self, path, size, x=None, y=None, w=None, h=None):
        self.size = size
        self.path = path
        # open a regular PIL image
        print('Tile init path', path)
        self.image = PIL.Image.open(open(path, 'rb'))
        # Crop the image based on x, y, w, h
        print('Tile init', 'x', x, 'y', y, 'w', w, 'h', h, 'path', path)
        if x != None and y != None and w != None and h != None:
            self.image = self.image.crop((x, y, x + w, y + h))
        # resize the image to size we want tiles
        self.image = self.image.resize((self.size, self.size))
        # convert image to a tk displayable image
        self.image = PIL.ImageTk.PhotoImage(self.image)


class TileMap():
    def __init__(self, parent, mapsizeX, mapsizeY):
        # sets the size of the map arrays
        self.mapsizeX = mapsizeX
        self.mapsizeY = mapsizeY
        self.parent = parent
        # create a tilemap matrix and a canvas object matrix of specified mapsize
        self.tilearray = []
        self.jsons = []
        self.relative_jsons = []
        for i in range(self.mapsizeY):
            row = []
            for j in range(self.mapsizeX):
                row.append(" ")  # fill them with spaces...
            self.tilearray.append(row)

        self.canvasarray = []
        for i in range(self.mapsizeY):
            row = []
            for j in range(self.mapsizeX):
                row.append(" ")
            self.canvasarray.append(row)

        self.componentNameArray = []
        for i in range(self.mapsizeY):
            row = []
            for j in range(self.mapsizeX):
                row.append(" ")
            self.componentNameArray.append(row)

    def OpenMap(self, path):
        try:
            file = open(path, "r")  # open specified path...
            whole = file.read()
            file.close()
            data = whole.split("\n")  # ...and split it into rows

            files = []  # make a holder for the paths to each tile image.
            for i, row in enumerate(data):
                if i > 6 and i < len(data) - 5 and row[13] == "i":
                    # remove the "        self.images.append(pygame.transform.scale(pygame.image.load("...
                    row = row[69:]
                    # ... and the "), (self.tilesize, self.tilesize)))" from the tile image path
                    row = row[:-36]
                    files.append(str(row))  # append file to file types

            listdata = []  # make an intermediate array to hold the tilemap data
            begin = False
            for i, row in enumerate(data):
                # skip everything until array declaration.
                if i > 6 and begin == False and row[13] == "a":
                    begin = True
                # get everything until the drawMap() function definition
                if begin == True and i < len(data) - 5:
                    listdata.append(row)

            # remove the python array declaration
            listdata[0] = listdata[0][23:]
            array = []  # make a final holder for the tilemap data
            for row in listdata:
                item = row.replace("]", "").replace("[", "").replace(
                    " ", "")  # remove all unneeded chars
                # split array into pieces with newline char
                item = item.split(",")
                try:  # if there is an empty "" left over...
                    # remove empty items left over from "]," at the end of each list
                    item.remove("")
                except:
                    pass
                array.append(item)  # add char to array

            self.NewFile()  # clear the program data.

            # make buttons for each loaded tile image.
            self.parent.ibox.imgcanv.MakeButton(files)
            for i, row in enumerate(array):
                for j, elim in enumerate(row):
                    if (int(elim) > 0):  # find each tile corresponding to an image
                        self.parent.ibox.imgcanv.selectTile(int(elim) - 1)
                        self.parent.cframe.cmap.tilepos = (j, i)
                        self.parent.cframe.cmap.setTile()  # draw it to the screen
        except:  # if there is an error loading file...
            # ask user if he/she would like to attempt to contiue anyway.
            mbox = messagebox.askyesno(
                title="Loading Error", message="There was an error loading file. The file has either been changed or is empty. Would you like to load it anyway?")
            if mbox == "no":  # if not..
                self.NewFile()  # clear the slate.

    def SaveMap(self, path, grabtype):
        pathtypes = []  # a list of all files that have already been detected during parsing
        # add a default value so that spaces will always have the 0 or null value
        pathtypes.append(" ")
        output = ""  # a list that holds the final file output
        filetype = ""
        count = 0
        # find the number of chars proceding the file extension...
        for char in str(path):
            if char == "." or char == "{":
                break
            count += 1  # store it in count...
        for i in range(len(path) - count):
            filetype += path[i + count]  # ...and use it to find the path

        if filetype != ".json" and filetype != ".py" and filetype != ".pyw" and filetype != ".csv":  # set default file type to .py
            filetype = ".json"  # if the user forgot to set his/her filetype when saving
            p2 = ""  # program automatically uses ".py" extension
            for i in range(count):  # the path must be fixed to match what the user entered
                p2 += path[i]
            path = p2 + filetype

        arraydata = []
        if False: # force full
        # if grabtype == "part":  # if this save want to compress the map for a final export...
            truncate_row = True  # this snippet will cut out all empty columns
            drop_rows_top = 0
            for row in self.tilearray:  # finds the number of empty rows above map's contents
                for tile in row:
                    if tile != " ":  # if row is not empty...
                        truncate_row = False  # stop truncating rows.
                        break
                if truncate_row == False:  # ...and break the loop
                    break
                drop_rows_top += 1  # update number of rows to drop on the top

            drop_rows_bottom = 0
            truncate_row_b = True
            # finds the number of empty rows below map's contents
            for row in reversed(self.tilearray):
                for tile in row:
                    if tile != " ":  # if row is not empty...
                        truncate_row_b = False  # stop truncating rows.
                        break
                if truncate_row_b == False:  # ...and break the loop
                    break
                drop_rows_bottom += 1  # update number of rows to drop on the bottom

            drop_col_left = self.mapsize - 1
            for row in self.tilearray:  # finds the number of empty columns left of map's contents
                col = 0
                for tile in row:
                    if tile != " ":  # this method increments through each row and finds the column with the...
                        # ...tile that is closest to the left in that row. This value is then used to ...
                        break
                    else:  # ...find the left most column.
                        col += 1  # update the number of columns to drop
                if drop_col_left > col:  # increment the number of columns to drop down from the total number of columns
                    drop_col_left = col

            drop_col_right = self.mapsize - 1
            for row in self.tilearray:
                col = 0
                # finds the number of empty columns right of map's contents
                for tile in reversed(row):
                    if tile != " ":  # this method increments through each row and finds the column with the...
                        # ...tile that is closest to the right in that row. This value is then used to ...
                        break
                    else:  # ...find the right most column.
                        col += 1
                if drop_col_right > col:  # increment the number of columns to drop down from the total number of columns
                    drop_col_right = col

            # cuts out all empty rows...
            for x in range(drop_rows_top, self.mapsize - drop_rows_bottom):
                row = []
                for y in range(drop_col_left, self.mapsize - drop_col_right):
                    # ...leaving only the map contents
                    row.append(self.tilearray[x][y])
                arraydata.append(row)
        else:
            # if the user does not want to compress output, use the entire map.
            arraydata = self.tilearray
        print(arraydata)
        
        jsons = self.parent.tmap.jsons[::-1]
        relative_jsons = self.parent.tmap.relative_jsons[::-1]
        # for row in arraydata:
        #     for tile in row:
        #         # print(tile)
        #         found = False
        #         count = 0
        #         for p in pathtypes:  # finds each image path and assigns it a number...
        #             if tile == p:
        #                 found = True
        #                 break
        #             else:
        #                 count += 1
        #         if found == False and tile != " " and tile != "":
        #             pathtypes.append(tile)
        #         # ...the numbers are added to the output
        #         output += str(count) + ","
        #     output += "\n"

        arraydata = []
        for row in self.tilearray:
            rowarray = []
            for tile_json_path in row:
                index = jsons.index(tile_json_path)+1 if tile_json_path in jsons else 0
                rowarray.append(index)
            arraydata.append(rowarray)

                
        try:  # use error handling in case file cannot be written to.
            # print(self.parent.ibox.loader.comps)
            data = output.split("\n")
            # print(filetype)
            if filetype == ".json":
                # paths = []
                paths = {}
                paths["tile_jsons"] = relative_jsons
                # Convert the data array to an array of arrays of integers
                # data_array = []
                # for row in data:
                #     if row:
                #         data_array.append([int(num)
                #                           for num in row.split(",") if num])

                paths["tile_array"] = arraydata
                # for i, pathImg in enumerate(pathtypes):
                #     if i > 0:
                #         for cmps in self.parent.ibox.loader.comps:
                #             keys_to_remove = ['filename',
                #                               'transformComponent', 'frames']
                #             if (os.path.abspath("../" + cmps['value']) == pathImg):
                #                 args = [
                #                     {"arg_name": "id", "arg_type": "int", "value": i}, {
                #                         "arg_name": "path", "arg_type": "string", "value": pathImg}
                #                 ]
                #                 for rarg in cmps['restArgs']:
                #                     if rarg['arg_name'] not in keys_to_remove:
                #                         args.append(rarg)
                #                 print(cmps['restArgs'])
                #                 paths.append(
                #                     {"component_type": cmps['name'], "args": args})
            


                # Create a dictionary with paths and data keys
                # output_dict = {"type_name": "test_tilemap",
                #                "components": paths, }

                # Convert the dictionary to a JSON string
                output_json = json.dumps(paths, indent=4)
                print(path)
                with open(path, "w") as file:
                    file.write(output_json)
                # file = open(path, "w") #output goes to file
                # file.write(output_json)
                # file.close()
            elif filetype == ".csv":  # if the user's selected filetype is .csv...
                file = open(path, "w")  # just dump the array data in the file
                file.write(output)
                file.close()
            # This code writes a python file that loads and draws a map using pygame.
            elif filetype == ".py" or filetype == ".pyw":
                output2 = '''import pygame

class TileMap():
    def __init__(self, tilesize):
        pygame.init()
        self.tilesize = tilesize
        self.images = []\n'''

                # write a line of code that loads a tile image...
                for i in range(len(pathtypes)):
                    if i > 0:  # for each tile that the user loaded.
                        output2 += '''        self.images.append(pygame.transform.scale(pygame.image.load("''' + str(
                            pathtypes[i]) + '''"), (self.tilesize, self.tilesize)))\n'''

                 # split the output string by the new line character splitting it into an array.
                # print(data)
                output2 += "        self.array = ["
                # write code to load the tile array.
                for i in range(len(data) - 1):
                    if i != 0:
                        output += "        "
                    output2 += "[" + data[i][:-1] + "],\n"
                output2 = output2[:-2] + "]\n"
                # make a function to draw all of the tiles to the screen
                output2 += '''    def drawMap(self, surface, location):
            for i,row in enumerate(self.array):
                for j,tile in enumerate(row):
                    if tile > 0:
                        surface.blit(self.images[tile - 1], (location[0] + j * self.tilesize, location[1] + i * self.tilesize))'''

                file = open(path, "w")  # output goes to file
                # file.write(output2)
                file.write(output_json)
                file.close()

        except Exception as e:
            print("Error:", e)
            messagebox.showwarning(message="File " + str(
                path) + " cannot be written to. Make sure it is not open in another program and then try again.")

    def NewFile(self):  # a function that clears the screen and array data.
        self.parent.tmap.jsons.clear()
        for i, row in enumerate(self.canvasarray):
            for j, tile in enumerate(row):
                # delete all tiles on the screen.
                self.parent.cframe.cmap.delete(tile)
                self.canvasarray[i][j] = ' '  # clear the canvas array
        for i, row in enumerate(self.tilearray):
            for j, tile in enumerate(row):
                self.tilearray[i][j] = ' '  # clear the tile array.
        # clear all tile buttons in the side box.
        self.parent.ibox.imgcanv.buttons.clear()
        for item in self.parent.ibox.imgcanv.winfo_children():
            item.destroy()

            # Set the starting position for button placement so original position
            self.parent.ibox.imgcanv.newbtnpos = (0, 0)
        self.parent.tbox.click()
