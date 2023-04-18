import os
import json
GRID_SIZE = 64
template = {
    "type_name": "name",
    "components": [
        {
            "component_type":"SpriteComponent",
            "args":[
                {"arg_name":"filename","arg_type":"string", "value":"./sprites/Tiles1.bmp"},
                {"arg_name":"transformComponent","arg_type":"TransformComponent"},
                {"arg_name":"x","arg_type":"int", "value":0},
                {"arg_name":"y","arg_type":"int", "value":0},
                {"arg_name":"w","arg_type":"int", "value":64},
                {"arg_name":"h","arg_type":"int", "value":64},
                {"arg_name":"frames","arg_type":"int", "value":1},
                {"arg_name":"numRows","arg_type":"int", "value":8},
                {"arg_name":"numCols","arg_type":"int", "value":8},
                {"arg_name":"forceScreenWidth", "arg_type":"int", "value":64},
                {"arg_name":"forceScreenHeight", "arg_type":"int", "value":64},
                {"arg_name":"rowOffset", "arg_type":"int", "value":0},
                {"arg_name":"colOffset", "arg_type":"int", "value":0}
            ]
        }
    ]
}
def generate(spritesheet_path, sheet_w, sheet_h, sprite_grid_size, out_dir):
    os.makedirs(out_dir, exist_ok=True)
    sheet_name = os.path.splitext(os.path.basename(spritesheet_path))[0]
    numRows = int(sheet_h / sprite_grid_size)
    numCols = int(sheet_w / sprite_grid_size)
    for i in range(numRows):
        for j in range(numCols):
            tile = template.copy()
            tile["type_name"] = sheet_name + "_" + str(i) + "_" + str(j)
            tile["components"][0]["args"][0]["value"] = spritesheet_path
            tile["components"][0]["args"][4]["value"] = sprite_grid_size
            tile["components"][0]["args"][5]["value"] = sprite_grid_size
            tile["components"][0]["args"][7]["value"] = numRows
            tile["components"][0]["args"][8]["value"] = numCols
            tile["components"][0]["args"][9]["value"] = GRID_SIZE
            tile["components"][0]["args"][10]["value"] = GRID_SIZE
            tile["components"][0]["args"][11]["value"] = i
            tile["components"][0]["args"][12]["value"] = j
            json.dump(tile, open(os.path.join(out_dir, tile["type_name"] + ".json"), "w"), indent=4)

if __name__ == "__main__":
    generate("./sprites/owlishmedia_trimmed.bmp", 416, 64, 32, './definitions/tiles/owlishmedia_trimmed/')