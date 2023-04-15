import mygameengine
import json

## @brief A dictionary of component name strings to their respective classes
COMPONENTS = {
    "ControllerComponent": mygameengine.ControllerComponent,
    "TransformComponent": mygameengine.TransformComponent,
    "SpriteComponent": mygameengine.SpriteComponent,
    "HealthBarComponent": mygameengine.HealthBarComponent,
    "CollisionComponent": mygameengine.CollisionComponent,
    "BehaviorComponent": mygameengine.BehaviorComponent,
    "CounterComponent": mygameengine.CounterComponent,
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
# @return A list of components
def create_components(go_def_json_object, transform_override=None):
    component_defs = go_def_json_object["components"]
    components = []

    for comp_def in component_defs:
        print("makging component of type: " + comp_def["component_type"])
        typed_args = []

        if comp_def["component_type"] == "TransformComponent" and transform_override:
            comp_def["args"] = []
            for a in transform_override:
                if a["param"] == "direction":
                    comp_def["args"].append(
                        {"arg_type": "Vec2", "x": int(a["x"]), "y": int(a["y"])}
                    )
                elif a["param"] == "position":
                    comp_def["args"].append(
                        {"arg_type": "Vec2", "x": int(a["x"]), "y": int(a["y"])}
                    )
                elif a["param"] == "controller":
                    comp_def["args"].append({"arg_type": "ControllerComponent"})
                elif a["param"] == "behavior":
                    comp_def["args"].append({"arg_type": "BehaviorComponent"})

        for raw_arg in comp_def["args"]:
            arg_type = raw_arg["arg_type"]
            if arg_type in BUILT_IN:
                typed_args.append(BUILT_IN[arg_type](raw_arg["value"]))
            elif arg_type in CUSTOM:
                params = raw_arg.copy()
                params.pop("arg_type")
                params = list(params.values())
                typed_args.append(CUSTOM[arg_type](*params))
            elif arg_type in COMPONENTS:
                matching_components = [
                    c for c in components if isinstance(c, COMPONENTS[arg_type])
                ]
                if len(matching_components) == 0:
                    raise ValueError(
                        "No matching component found for type: " + arg_type
                    )
                typed_args.append(matching_components[0])
            elif arg_type == "CollisionCallbacks":
                collision_callbacks = raw_arg["value"]
                list_variables_set = collision_callbacks.get("variables_set", {})
                list_variables_increment = collision_callbacks.get("variables_increment", {})
                list_bool_true = collision_callbacks.get("bools_true", [])
                list_bool_false = collision_callbacks.get("bools_false", [])
                list_bool_toggle = collision_callbacks.get("bools_toggle", [])

                typed_args.append(list_variables_set)
                typed_args.append(list_variables_increment)
                typed_args.append(list_bool_true)
                typed_args.append(list_bool_false)
                typed_args.append(list_bool_toggle)
            else:
                raise ValueError("Type not found: " + arg_type)

        constructor = COMPONENTS[comp_def["component_type"]]
        component = constructor(*typed_args)
        components.append(component)

    return components


## @brief Creates a game object from a json type definition file
# @details The type definition file contains the definition for a game object type.
# @param id The (in-game/in-engine) id of the game object
# @param json_path The path to the json type definition file
# @param transform_override A list of transform parameters to override the transform component
# @return A game object
def create_go(id, json_path, transform_override=None):
    with open(json_path) as json_data_file:
        go_def_json_object = json.load(json_data_file)
    type_name = go_def_json_object["type_name"]
    print("Creating game object of type: " + type_name)
    components = create_components(
        go_def_json_object, transform_override=transform_override
    )
    go = mygameengine.GameObject(id)
    for i in range(len(components)):
        print("adding component: ", components[i])
        # NOTE: component id using index for now is the correct way, even though hacky
        go.AddComponent(str(i), components[i])
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
        transform_override = None
        if "transform_override" in game_object_def:
            transform_override = game_object_def["transform_override"]
        go = create_go(
            game_object_def["name"],
            game_object_def["definition_file"],
            transform_override=transform_override,
        )
        game_objects.append((game_object_def["name"], go))
    return game_objects
