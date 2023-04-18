import os
import sys
import argparse
import shutil

ENGINE_BUILD_FILE = {
    "MAC": "Assets/buildscripts/macbuild.py",
    "LINUX": "Assets/buildscripts/linuxbuild.py",
}

def exclude_directories(src, names, excluded_dirs):
    return set(excluded_dirs)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Build script options')
    parser.add_argument('--platform', required=True, choices=['LINUX', 'MAC'], help='The platform to build for')
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--all', action='store_true', help='Build everything')
    group.add_argument('--game-only', action='store_true', help='Build game only')
    group.add_argument('--engine-only', action='store_true', help='Build engine only')

    args = parser.parse_args()

    try:
        shutil.rmtree("bin", ignore_errors=True)
        shutil.rmtree("tmp", ignore_errors=True)
        os.makedirs("tmp", exist_ok=True)
        os.makedirs("bin", exist_ok=True)
        if args.game_only:
            print(f"Building game only for platform {args.platform}")
            os.system("pyinstaller --onefile --additional-hooks-dir=. --distpath=tmp/dist --workpath=tmp/build -n TinyEngineGame MyScript.py")
        elif args.engine_only:
            print(f"Building engine only for platform {args.platform}")
            os.system(f"python {ENGINE_BUILD_FILE[args.platform]}")
        else:
            print(f"Building everything for platform {args.platform}")
            os.system(f"python {ENGINE_BUILD_FILE[args.platform]}")
            os.system("pyinstaller --onefile --additional-hooks-dir=. --distpath=tmp/dist --workpath=tmp/build -n TinyEngineGame MyScript.py")
        

    except Exception as e:
        print(f"Build failed. Error: {e}")
        shutil.rmtree("tmp")
        exit(-1)
    finally: 
        if args.game_only:
            os.rename("tmp/dist/TinyEngineGame", "bin/TinyEngineGame")
            shutil.rmtree("tmp")
        elif args.engine_only:
            os.rename("mygameengine.so", "bin/mygameengine.so")
        else:
            os.rename("tmp/dist/TinyEngineGame", "bin/TinyEngineGame")
            os.rename("mygameengine.so", "bin/mygameengine.so")
            shutil.rmtree("tmp")
        shutil.copytree("Assets", "bin/Assets", ignore=lambda src,names: exclude_directories(src, names, ["buildscripts", "__pycache__", "*/__pycache__"]))
        # shutil.copytree("Assets/definitions", "bin/Assets/definitions", dirs_exist_ok=True)
        # shutil.copytree("Assets/scripts", "bin/Assets/scripts", dirs_exist_ok=True)
        # shutil.copytree("Assets/sprites", "bin/Assets/sprites", dirs_exist_ok=True)
        print("Build finished. Run the game with the following command:")
        print("    ./bin/TinyEngineGame <optional:override scene definition file>")
        print("Note that you will need an Asset folder for the game to run.")
        print("A sample asset folder is provided in the bin folder for you.")
        print("File structure:")
        print("""
            .
            └── Assets
                ├── definitions
                │   ├── game_objects
                │   ├── scenes
                │   ├── tilemaps
                │   └── tiles
                ├── scripts
                └── sprites
            └── TinyEngineGame""")

