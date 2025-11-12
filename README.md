### CS213-FunBox

> [!CAUTION]
> work in progress
>

> Game Dev assignment as part of the OOP course in FCAI - CU, 2025.

Funbox is a board games project that utilizes a reusable OOP framework in C++ for individual and group games.

> [!IMPORTANT]
> These are instructions related to the developement of our game, meant for my fellow developers.

Suppose we are creating a new game, called XYZ, there are files that need to be created or changed each time.


#### (1) The following files need to be made every time we make a new game. For the game "XYZ" for example:

```bash
include/XYZ_Classes.h       # make a header file for the game’s classes
src/XYZ_Classes.cpp         # class implementation
src/XYZ_Game.cpp            # launch function (calls GameManager, launches game)
```

#### (2) Every time we make a game, we need to add a function for it in `include/GameLaunchers.h`. we follow this pattern:

```cpp
namespace GameLaunchers {
    void launch_xo_game();
    void launch_sus_game();
    // ... more of our games
    void launch_xyz_game(); // << we add a new launch for the new game
}
```

#### (3) We add a new case in the switch statement in main.cpp:

```cpp
case 3: GameLaunchers::launch_xyz_game(); break;
```
Everytime, also in main.cpp, we add a new option to the menu by using:

`mainMenu.addOption("Play XYZ");`



#### (4) when making any new source file (any new file that has the extension .cpp) 
##### you must add it in cmakelists.txt

```
set(SOURCES
    ${SRC_DIR}/Main.cpp
    // ...
    // other .cpp files 
    ${SRC_DIR}/XYZ_Game.cpp    # << we add the newly created files
    ${SRC_DIR}/XYZ_Classes.cpp # << any .cpp file in /src is added.
)

```

> [!WARNING]
> MAKE SURE TO FOLLOW THIS CHECKLIST WHEN CREATING A NEW GAME SO THAT WE DONT RUN INTO BUILD ERRORS

| Step | File                           | Change                                                            |
| ---- | ------------------------------ | ----------------------------------------------------------------- |
| 1    | `include/XYZ_Classes.h`        | Create new header                                                 |
| 2    | `src/XYZ_Classes.cpp`          | Create implementation                                             |
| 3    | `src/XYZ_Game.cpp`             | Create launcher                                                   |
| 4    | `include/GameLaunchers.h`      | Add `launch_xyz_game()`                                           |
| 5    | `src/Main.cpp`                 | Add new `switch` case for game                                    |
| 5    | `src/Main.cpp`                 | Add new `mainMenu.addOption("game name")`                         |
| 6    | `CMakeLists.txt`               | Add new `.cpp` files                                              |


