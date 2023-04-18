## Add any additional notes here

To compile from source, please install pyinstaller first using `pip install pyinstaller`.
Detailed documentations and guides on compiltation, running the game, ***making your own game*** can be found in the [project website](https://www.notion.so/overainy/66c87ddd2bf046b28e13c338e87ba776?v=7da32e3a48734b65bf7ae694c18acb38&pvs=4). Scroll down for more pages. Make sure to check it out!

## Game/Engine Publicity

**Project Website**: https://overainy.notion.site/66c87ddd2bf046b28e13c338e87ba776?v=7da32e3a48734b65bf7ae694c18acb38

## Compilation Instructions
See [this page](https://www.notion.so/overainy/How-to-Compile-248225d8e1dd4c77815eb094d2d9d972?pvs=4) in project website for detailed compilation instructions.

For compiling binary files for MAC users, please run `python build.py --platform=MAC --all` under `Engine` directory. 

For Linux users, run `python build.py --platform=LINUX --all` under `Engine` directory.

Then to start Pacman, please run `./TinyEngineGame` inside `bin` folder. You may also refer to [this page](https://www.notion.so/overainy/How-to-run-Pacman-0694044136dd4efdb7117d69134b1ab2?pvs=4) for further instructions.

No support for Windows as of now.


## Project Hieararchy

In the future, other engineers may take on our project, so we have to keep it organized given the following requirements below. Forming some good organization habits now will help us later on when our project grows as well. These are the required files you should have 

### ./Engine Directory Organization

- Docs 
    - Source Code Documentation
- Assets
    - Art assets (With the Sub directories music, sound, images, and anything else)
- src
    - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
    - header files(.h and .hpp files)
- lib
    - libraries (.so, .dll, .a, .dylib files). Note this is a good place to put SDL
- bin
    - This is the directory where your built executable(.exe for windows, .app for Mac, or a.out for Linux) and any additional generated files are put after each build.
- EngineBuild (Optional)
    - You may optionally put a .zip to you final deliverable. One should be able to copy and paste this directory, and only this directory onto another machine and be able to run the game. This is optional because for this course we will be building your projects from source. However, in the game industry it is useful to always have a build of a game ready for testers, thus a game project hieararchy would likely have this directory in a repo or other storage medium.
- ThirdParty
    - Code that you have not written if any.

**Note: For the final project you may add additional directories if you like, for example for your game which demonstrates your engine works.** 

**Additional Notes:** 

1. src and include should only contain ".cpp" or ".hpp" files. Why? It makes it very fast to do a backup of your game project as one example. Secondly, binary files that are generated often clutter up directories. I should not see any binaries in your repository, you may use a '.gitignore' file to help prevent this automatically. 
