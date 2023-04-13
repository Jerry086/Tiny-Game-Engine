import mygameengine
import json

COMPONENTS = {
    "ControllerComponent": mygameengine.ControllerComponent,
    "TransformComponent": mygameengine.TransformComponent,
    "SpriteComponent": mygameengine.SpriteComponent,
    "TileMapComponent": mygameengine.TileMapComponent,
    "HealthBarComponent": mygameengine.HealthBarComponent,
    "CollisionComponent": mygameengine.CollisionComponent,
    "BehaviorComponent": mygameengine.BehaviorComponent,
    "CounterComponent": mygameengine.CounterComponent,
}

BUILT_IN = {
    "int": int,
    "float": float,
    "string": str,
}

CUSTOM = {
    "Vec2": mygameengine.Vec2,
}


def read_json(json_path):
    with open(json_path) as json_data_file:
        data = json.load(json_data_file)
    return data


def create_components(go_def_json_object, transform_override=None):
    type_name = go_def_json_object["type_name"]
    print("Creating game object of type: " + type_name)
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
            else:
                raise ValueError("Type not found: " + arg_type)

        constructor = COMPONENTS[comp_def["component_type"]]
        component = constructor(*typed_args)
        components.append(component)

    return components


def create_go(id, json_path, transform_override=None):
    with open(json_path) as json_data_file:
        go_def_json_object = json.load(json_data_file)
    components = create_components(
        go_def_json_object, transform_override=transform_override
    )
    go = mygameengine.GameObject(id)
    for i in range(len(components)):
        print("adding component: ", components[i])
        # NOTE: component id using index for now is the correct way, even though hacky
        go.AddComponent(str(i), components[i])
    return go


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
