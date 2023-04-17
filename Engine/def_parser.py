import mygameengine
import json

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


## @brief Creates a list of components for a game object from a type definition json object
#  @param go_def_json_object The json object containing the type definition for a game object type
# @param transform_override A list of transform parameters to override the transform component
# @return A list of tuples of (component name, component)
# def create_components(go_def_json_object, transform_override=None):
#     component_defs = go_def_json_object["components"]
#     components = []

#     for comp_def in component_defs:
#         print("makging component of type: " + comp_def["component_type"])
#         typed_args = []

#         if (
#             comp_def["component_type"] == "TransformComponent"
#             and transform_override
#         ):
#             comp_def["args"] = []
#             for a in transform_override:
#                 if a["param"] == "direction":
#                     comp_def["args"].append(
#                         {"arg_type": "Vec2", "x": int(a["x"]), "y": int(a["y"])}
#                     )
#                 elif a["param"] == "position":
#                     comp_def["args"].append(
#                         {"arg_type": "Vec2", "x": int(a["x"]), "y": int(a["y"])}
#                     )
#                 elif a["param"] == "controller":
#                     comp_def["args"].append({"arg_type": "ControllerComponent"})
#                 elif a["param"] == "behavior":
#                     comp_def["args"].append({"arg_type": "BehaviorComponent"})

#         for raw_arg in comp_def["args"]:
#             arg_type = raw_arg["arg_type"]
#             if arg_type in BUILT_IN:
#                 typed_args.append(BUILT_IN[arg_type](raw_arg["value"]))
#             elif arg_type in CUSTOM:
#                 params = raw_arg.copy()
#                 params.pop("arg_type")
#                 params = list(params.values())
#                 typed_args.append(CUSTOM[arg_type](*params))
#             elif arg_type in COMPONENTS:
#                 matching_components = [
#                     c
#                     for _, c in components
#                     if isinstance(c, COMPONENTS[arg_type])
#                 ]
#                 if len(matching_components) == 0:
#                     raise ValueError(
#                         "No matching component found for type: " + arg_type
#                     )
#                 typed_args.append(matching_components[0])
#             else:
#                 print ("Type not found: ", arg_type, ". Skipping this argument.")

#         constructor = COMPONENTS[comp_def["component_type"]]
#         component = constructor(*typed_args)
#         if "start_disabled" in comp_def.keys() and comp_def["start_disabled"]:
#             component.m_enabled = False
#         components.append((comp_def["component_type"], component))
#     return components
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
                        {"arg_name":"direction", "arg_type": "Vec2", "x": int(a["x"]), "y": int(a["y"])}
                    )
                elif a["param"] == "position":
                    comp_def["args"].append(
                        {"arg_name":"position", "arg_type": "Vec2", "x": int(a["x"]), "y": int(a["y"])}
                    )
                elif a["param"] == "controller":
                    comp_def["args"].append({"arg_name": "controllerComponent", "arg_type": "ControllerComponent"})
                elif a["param"] == "behavior":
                    comp_def["args"].append({"arg_name": "controllerComponent", "arg_type": "BehaviorComponent"})

        for raw_arg in comp_def["args"]:
            print(raw_arg)
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
def create_go(name, json_path, transform_override=None, go_script_module=None):
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


# @brief Creates a scene from a json scene definition file
# @details A scene is a list of game objects. The scene definition file contains a list of game object definitions.
# @param json_path The path to the json scene definition file
# @return A list of game objects
def create_scene(json_path):
    with open(json_path) as json_data_file:
        scene_def_json_object = json.load(json_data_file)

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
            game_object_def["definition_file"],
            transform_override=transform_override,
            go_script_module=go_script_module
        )
        if "start_disabled" in game_object_def and game_object_def["start_disabled"]:
            go.m_enabled = False
        game_objects.append((game_object_def["name"], go))
    return game_objects

def make_component_dict(*args, **kwargs):
    if "component_type" not in kwargs.keys():
        raise ValueError("component_type not found in kwargs")

    component_type = kwargs["component_type"]
    if component_type not in COMPONENTS.keys():
        raise ValueError("component_type not found in COMPONENTS")
    res = {
        "component_type": kwargs["component_type"],
        "args": []
    }
    kwargs.pop("component_type")
    for item in kwargs.items():
        key_as_comp_name = item[0][0].upper() + item[0][1:]
        if item[0] in ["position", "direction"]:
            res["args"].append({"arg_name": item[0], "arg_type": "Vec2", "x": item[1][0], "y": item[1][1]})
        elif item[0] in ["filename"]:
            res["args"].append({"arg_name": item[0], "arg_type": "string", "value": item[1]})
        elif key_as_comp_name in COMPONENTS.keys():
            print("in inner")
            res["args"].append({"arg_name": item[0], "arg_type": item[0][0].upper() + item[0][1:]})
            continue
        elif isinstance(item[1], float):
            res["args"].append({"arg_name": item[0], "arg_type": "float","value": item[1]})
        elif isinstance(item[1], int):
            res["args"].append({"arg_name": item[0], "arg_type": "int","value": item[1]})
        else:
            res["args"].append({"arg_name": item[0], "arg_type": "string","value": item[1]})
        
    return res

        

if __name__ == '__main__':
    controller_comp = make_component_dict(component_type="ControllerComponent")

    param_dict = {
        "component_type": "TransformComponent",
        "position": (0, 0),
        "direction": (1, 0),
        "controllerComponent": "ControllerComponent"
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
        "frames":10
    }
    collision_param = {
        "component_type": "CollisionComponent",
        "objectType": "player",
        "transformComponent": "",
        "w": 10,
        "h": 10
    }
    sprite_comp = make_component_dict(**sprite_dict)
    collision_comp = make_component_dict(**collision_param)
    go_def = {"components":[controller_comp, transform_comp, sprite_comp, collision_comp]}
    print(go_def)
    components = create_components(go_def)
    print(components)