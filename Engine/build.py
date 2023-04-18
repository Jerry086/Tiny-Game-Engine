import os
import sys
import argparse
import shutil

ENGINE_BUILD_FILE = {
    "MAC": "./Assets/buildscripts/macbuild.py",
    "LINUX": "./Assets/buildscripts/linuxbuild.py",
}

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Build script options')
    parser.add_argument('--platform', required=True, choices=['LINUX', 'MAC'], help='The platform to build for')
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--all', action='store_true', help='Build everything')
    group.add_argument('--game-only', action='store_true', help='Build game only')
    group.add_argument('--engine-only', action='store_true', help='Build engine only')

    args = parser.parse_args()

    try:
        os.makedirs("tmp", exist_ok=True)
        os.makedirs("bin", exist_ok=True)
        if args.game_only:
            print(f"Building game only for platform {args.platform}")
            os.system("pyinstaller --onefile --additional-hooks-dir=./buildscripts --distpath=tmp/dist --workpath=tmp/build -n TinyEngineGame MyScript.py")
        elif args.engine_only:
            print(f"Building engine only for platform {args.platform}")
            os.system(f"python {ENGINE_BUILD_FILE[args.platform]}")
        else:
            print(f"Building everything for platform {args.platform}")
            os.system(f"python {ENGINE_BUILD_FILE[args.platform]}")
            os.system("pyinstaller --onefile --additional-hooks-dir=./buildscripts --distpath=tmp/dist --workpath=tmp/build -n TinyEngineGame MyScript.py")
        

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
        shutil.copytree("definitions", "bin/definitions", dirs_exist_ok=True)
        shutil.copytree("scripts", "bin/scripts", dirs_exist_ok=True)
        shutil.copytree("sprites", "bin/sprites", dirs_exist_ok=True)
        print("Build finished. Run the game with the following command:")
        print("    ./bin/TinyEngineGame <optional:override scene definition file>")

