import mygameengine
import json

GRID_SIZE = 64

## @brief A dictionary of component name strings to their respective classes
COMPONENTS = {
    "ControllerComponent": mygameengine.ControllerComponent,
    "TransformComponent": mygameengine.TransformComponent,
    "SpriteComponent": mygameengine.SpriteComponent,
    "CollisionComponent": mygameengine.CollisionComponent,
    "BehaviorComponent": mygameengine.BehaviorComponent,
}

## @brief A dictionary of built in types name strings to their respective classes
BUILT_IN = {
    "int": int,
    "float": float,
    "string": str,
}

## @brief A dictionary of custom types name strings to their respective classes
CUSTOM = {
    "Vec2": mygameengine.Vec2,
}


## @brief Reads a json file and returns the json object
#  @param json_path The path to the json file
#  @return The json object
def read_json(json_path):
    with open(json_path) as json_data_file:
        data = json.load(json_data_file)
    return data


# def get_kwargs(comp_def):
#     kwargs = {}
#     for raw_arg in comp_def["args"]:
#         arg_type = raw_arg["arg_type"]
#         arg_name = raw_arg["arg_name"]
#         if arg_type in BUILT_IN:
#             kwargs[arg_name] = BUILT_IN[arg_type](raw_arg["value"])
#         elif arg_type in CUSTOM:
#             params = raw_arg.copy()
#             params.pop("arg_type")
#             params.pop("arg_name")
#             kwargs[arg_name] = CUSTOM[arg_type](**params)
#         elif arg_type in COMPONENTS:
#             matching_components = [
#                 c
#                 for _, c in components
#                 if isinstance(c, COMPONENTS[arg_type])
#             ]
#             if len(matching_components) == 0:
#                 raise ValueError(
#                     "No matching component found for type: " + arg_type
#                 )
#             kwargs[arg_name] = matching_components[0]
#         else:
#             raise ValueError("Unknown type: " + arg_type)
#     return kwargs


## @brief Creates a list of components for a game object from a type definition json object
#  @param go_def_json_object The json object containing the type definition for a game object type
# @param transform_override A list of transform parameters to override the transform component
# @return A list of tuples of (component name, component)
def create_components(go_def_json_object, transform_override=None):
    component_defs = go_def_json_object["components"]
    components = []

    for comp_def in component_defs:
        print("making component of type: " + comp_def["component_type"])
        typed_kwargs = {}

        if (
            comp_def["component_type"] == "TransformComponent"
            and transform_override
        ):
            comp_def["args"] = []
            for a in transform_override:
                if a["param"] == "direction":
                    comp_def["args"].append(
                        {
                            "arg_name": "direction",
                            "arg_type": "Vec2",
                            "x": int(a["x"]),
                            "y": int(a["y"]),
                        }
                    )
                elif a["param"] == "position":
                    comp_def["args"].append(
                        {
                            "arg_name": "position",
                            "arg_type": "Vec2",
                            "x": int(a["x"]),
                            "y": int(a["y"]),
                        }
                    )
                elif a["param"] == "controller":
                    comp_def["args"].append(
                        {
                            "arg_name": "controllerComponent",
                            "arg_type": "ControllerComponent",
                        }
                    )
                elif a["param"] == "behavior":
                    comp_def["args"].append(
                        {
                            "arg_name": "controllerComponent",
                            "arg_type": "BehaviorComponent",
                        }
                    )

        for raw_arg in comp_def["args"]:
            arg_type = raw_arg["arg_type"]
            arg_name = raw_arg["arg_name"]
            if arg_type in BUILT_IN:
                typed_kwargs[arg_name] = BUILT_IN[arg_type](raw_arg["value"])
            elif arg_type in CUSTOM:
                params = raw_arg.copy()
                params.pop("arg_type")
                params.pop("arg_name")
                typed_kwargs[arg_name] = CUSTOM[arg_type](**params)
            elif arg_type in COMPONENTS:
                matching_components = [
                    c
                    for _, c in components
                    if isinstance(c, COMPONENTS[arg_type])
                ]
                if len(matching_components) == 0:
                    raise ValueError(
                        "No matching component found for type: " + arg_type
                    )
                typed_kwargs[arg_name] = matching_components[0]
            else:
                print("Type not found: ", arg_type, ". Skipping this argument.")
        constructor = COMPONENTS[comp_def["component_type"]]
        component = constructor(**typed_kwargs)
        if "start_disabled" in comp_def.keys() and comp_def["start_disabled"]:
            component.m_enabled = False
        components.append((comp_def["component_type"], component))
    return components


## @brief Creates a game object from a json type definition file
# @details The type definition file contains the definition for a game object type.
# @param id The (in-game/in-engine) id of the game object
# @param json_path The path to the json type definition file
# @param transform_override A list of transform parameters to override the transform component
# @return A game object
def create_go(
    name,
    json_obj=None,
    json_path=None,
    transform_override=None,
    go_script_module=None,
):
    if not json_obj and not json_path:
        raise ValueError("Must provide either json_obj or json_path")
    if json_obj:
        go_def_json_object = json_obj
    elif json_path:
        with open(json_path) as json_data_file:
            go_def_json_object = json.load(json_data_file)
    type_name = go_def_json_object["type_name"]
    print("Creating game object of type: " + type_name, "with name: " + name)
    components = create_components(
        go_def_json_object, transform_override=transform_override
    )
    go = mygameengine.GameObject(name)

    if "script_module" in go_def_json_object.keys():
        type_script_module = go_def_json_object["script_module"]
        go.SetPythonScriptModuleName(type_script_module)

    if go_script_module:
        go.SetPythonScriptModuleName(go_script_module)

    for comp_name, component in components:
        print("adding component: ", comp_name, "as", name + "_" + comp_name)
        component.m_name = comp_name
        go.AddComponent(name + "_" + comp_name, component)
    return go


def create_tilemap(tilemap_json_object):
    if (
        "TileMapComponent"
        not in tilemap_json_object["components"][-1]["component_type"]
    ):
        raise ValueError(
            "TileMapComponent must be the last component in the tilemap definition file"
        )
    tilemap_game_objects = []
    tilemap_comp_json = tilemap_json_object["components"].pop()
    array2D = tilemap_comp_json["args"][0]["value"]
    tile_index_to_bad_sprite_jsonarg_dict = {}
    sprite_jsonarg_template = {
        "component_type": "SpriteComponent",
        "args": [
            {
                "arg_name": "filename",
                "arg_type": "string",
                "value": "./sprites/Tiles1.bmp",
            },
            {
                "arg_name": "transformComponent",
                "arg_type": "TransformComponent",
            },
            {"arg_name": "x", "arg_type": "int", "value": 0},
            {"arg_name": "y", "arg_type": "int", "value": 0},
            {"arg_name": "w", "arg_type": "int", "value": 64},
            {"arg_name": "h", "arg_type": "int", "value": 64},
            {"arg_name": "frames", "arg_type": "int", "value": 1},
            {"arg_name": "numRows", "arg_type": "int", "value": 8},
            {"arg_name": "numCols", "arg_type": "int", "value": 8},
            {"arg_name": "forceScreenWidth", "arg_type": "int", "value": 64},
            {"arg_name": "forceScreenHeight", "arg_type": "int", "value": 64},
            {"arg_name": "rowOffset", "arg_type": "int", "value": 0},
            {"arg_name": "colOffset", "arg_type": "int", "value": 0},
        ],
    }
    transform_jsonarg_template = {
        "component_type": "TransformComponent",
        "args": [
            {"arg_name": "position", "arg_type": "Vec2", "x": 300, "y": 500}
        ],
    }
    collision_jsonarg_template = {
        "component_type": "CollisionComponent",
        "args": [
            {"arg_name": "objectType", "arg_type": "string", "value": "wall"},
            {
                "arg_name": "transformComponent",
                "arg_type": "TransformComponent",
            },
            {"arg_name": "w", "arg_type": "int", "value": 64},
            {"arg_name": "h", "arg_type": "int", "value": 64},
        ],
    }
    for i in range(len(tilemap_json_object["components"])):
        args = tilemap_json_object["components"][i]["args"]
        print("tilemap arg", tilemap_json_object["components"][i])
        if (
            "SpriteComponent"
            not in tilemap_json_object["components"][i]["component_type"]
        ):
            raise ValueError(
                "Tilemap definition file cannot contain components other than SpriteComponent and TileMapComponent"
            )
        tile_index_to_bad_sprite_jsonarg_dict[i] = tilemap_json_object[
            "components"
        ][i]
    print('size of tile_index_to_bad_sprite_jsonarg_dict',len( tile_index_to_bad_sprite_jsonarg_dict))
    for i in range(len(array2D)):
        for j in range(len(array2D[i])):
            tile_index = array2D[i][j] - 1
            print("making go for tile at row col", i, j, "with index", tile_index)
            if tile_index < 0 or tile_index >= len(tile_index_to_bad_sprite_jsonarg_dict):
                continue
            sprite_bad_jsonarg = tile_index_to_bad_sprite_jsonarg_dict[tile_index]
            sprite_jsonarg = sprite_jsonarg_template.copy()
            for argname, argtype, argvalue in sprite_bad_jsonarg["args"]:
                if argname == "transformComponent" or argname == "objectType" or argname == 'id':
                    continue
                if argname == "path":
                    sprite_jsonarg["args"][0]["value"] = argvalue
                    continue
                for arg in sprite_jsonarg["args"]:
                    if arg["arg_name"] == argname:
                        arg["value"] = argvalue
            print("sprite_jsonarg", sprite_jsonarg)
            w, h = 0, 0
            for arg in sprite_jsonarg["args"]:
                if arg["arg_name"] == "w":
                    w = arg["value"]
                elif arg["arg_name"] == "h":
                    h = arg["value"]
            # rowOffset = sprite_kwargs['rowOffset'] if 'rowOffset' in sprite_kwargs.keys() else 0
            # colOffset = sprite_kwargs['colOffset'] if 'colOffset' in sprite_kwargs.keys() else 0
            x, y = j * GRID_SIZE , i * GRID_SIZE
            print("x", x, "y", y, "w", w, "h", h)
            collision_jsonarg = collision_jsonarg_template.copy()
            collision_jsonarg["args"][2]["value"] = w
            collision_jsonarg["args"][3]["value"] = h
            transform_jsonarg = transform_jsonarg_template.copy()
            transform_jsonarg["args"][0]["x"] = x
            transform_jsonarg["args"][0]["y"] = y
            go_name = "tile_" + str(i) + "_" + str(j)
            go_json_obj = {}
            go_json_obj["type_name"] = go_name
            go_json_obj["components"] = [
                transform_jsonarg,
                sprite_jsonarg,
                collision_jsonarg,
            ]
            tilemap_game_objects.append(
                (go_name, create_go(go_name, json_obj=go_json_obj))
            )
    return tilemap_game_objects


# @brief Creates a scene from a json scene definition file
# @details A scene is a list of game objects. The scene definition file contains a list of game object definitions.
# @param json_path The path to the json scene definition file
# @return A list of game objects
def create_scene(scene_def_json_path):
    with open(scene_def_json_path) as scene_def_json_file:
        scene_def_json_object = json.load(scene_def_json_file)

    tilemap_path = scene_def_json_object["tilemap_definition"]
    with open(tilemap_path) as tilemap_json_file:
        tilemap_json_object = json.load(tilemap_json_file)

    game_objects = []
    game_object_defs = scene_def_json_object["game_objects"]
    for game_object_def in game_object_defs:
        transform_override, go_script_module = None, None
        if "transform_override" in game_object_def:
            transform_override = game_object_def["transform_override"]
        if "script_module" in game_object_def:
            go_script_module = game_object_def["script_module"]
        go = create_go(
            game_object_def["name"],
            json_path=game_object_def["definition_file"],
            transform_override=transform_override,
            go_script_module=go_script_module,
        )
        if (
            "start_disabled" in game_object_def
            and game_object_def["start_disabled"]
        ):
            go.m_enabled = False
        game_objects.append((game_object_def["name"], go))
    tilemap_game_objects = create_tilemap(tilemap_json_object)
    game_objects.extend(tilemap_game_objects)
    return game_objects


def make_component_dict(*args, **kwargs):
    if "component_type" not in kwargs.keys():
        raise ValueError("component_type not found in kwargs")

    component_type = kwargs["component_type"]
    if component_type not in COMPONENTS.keys():
        raise ValueError("component_type not found in COMPONENTS")
    res = {"component_type": kwargs["component_type"], "args": []}
    kwargs.pop("component_type")
    for item in kwargs.items():
        key_as_comp_name = item[0][0].upper() + item[0][1:]
        if item[0] in ["position", "direction"]:
            res["args"].append(
                {
                    "arg_name": item[0],
                    "arg_type": "Vec2",
                    "x": item[1][0],
                    "y": item[1][1],
                }
            )
        elif item[0] in ["filename"]:
            res["args"].append(
                {"arg_name": item[0], "arg_type": "string", "value": item[1]}
            )
        elif key_as_comp_name in COMPONENTS.keys():
            res["args"].append(
                {
                    "arg_name": item[0],
                    "arg_type": item[0][0].upper() + item[0][1:],
                }
            )
            continue
        elif isinstance(item[1], float):
            res["args"].append(
                {"arg_name": item[0], "arg_type": "float", "value": item[1]}
            )
        elif isinstance(item[1], int):
            res["args"].append(
                {"arg_name": item[0], "arg_type": "int", "value": item[1]}
            )
        else:
            res["args"].append(
                {"arg_name": item[0], "arg_type": "string", "value": item[1]}
            )

    return res


if __name__ == "__main__":
    controller_comp = make_component_dict(component_type="ControllerComponent")

    param_dict = {
        "component_type": "TransformComponent",
        "position": (0, 0),
        "direction": (1, 0),
        "controllerComponent": "ControllerComponent",
    }
    transform_comp = make_component_dict(**param_dict)

    sprite_dict = {
        "filename": "./sprites/gameOver.png",
        "component_type": "SpriteComponent",
        "x": 0,
        "y": 0,
        "w": 654,
        "h": 432,
        "transformComponent": "",
        "numRows": 1,
        "numCols": 1,
        "frames": 10,
    }
    collision_param = {
        "component_type": "CollisionComponent",
        "objectType": "player",
        "transformComponent": "",
        "w": 10,
        "h": 10,
    }
    sprite_comp = make_component_dict(**sprite_dict)
    collision_comp = make_component_dict(**collision_param)
    go_def = {
        "components": [
            controller_comp,
            transform_comp,
            sprite_comp,
            collision_comp,
        ]
    }
    print(go_def)
    components = create_components(go_def)
    print(components)
