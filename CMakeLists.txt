cmake_minimum_required(VERSION 3.15)
project(BoardGameApp)

#  C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
#Header files
include_directories(${INCLUDE_DIR})


# src files
set(SOURCES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Menu.cpp

    # ========================
    # Group (XO and SUS)
    ${SRC_DIR}/group/XO_Classes.cpp
    ${SRC_DIR}/group/XO_Game.cpp
    ${SRC_DIR}/group/MemoryTicTacToe_Classes.cpp
    ${SRC_DIR}/group/MemoryTicTacToe_Game.cpp

    # ========================
    # Abdallah
    ${SRC_DIR}/abdallah/ObstaclesTicTacToe_Classes.cpp
    ${SRC_DIR}/abdallah/ObstaclesTicTacToe_Game.cpp
    ${SRC_DIR}/abdallah/TicTacToe5x5_Classes.cpp
    ${SRC_DIR}/abdallah/TicTacToe5x5_Game.cpp
    ${SRC_DIR}/abdallah/WordTicTacToe_Classes.cpp
    ${SRC_DIR}/abdallah/WordTicTacToe_Game.cpp

    # ========================
    # Mostafa 
    ${SRC_DIR}/mostafa/DiamondTicTacToe_Classes.cpp
    ${SRC_DIR}/mostafa/DiamondTicTacToe_Game.cpp
    ${SRC_DIR}/mostafa/InfinityTicTacToe_Classes.cpp
    ${SRC_DIR}/mostafa/InfinityTicTacToe_Game.cpp
    ${SRC_DIR}/mostafa/MisereTicTacToe_Classes.cpp
    ${SRC_DIR}/mostafa/MisereTicTacToe_Game.cpp

    # ========================
    # Ammen 
    ${SRC_DIR}/ammen/PyramidTicTacToe_Classes.cpp
    ${SRC_DIR}/ammen/PyramidTicTacToe_Game.cpp
    ${SRC_DIR}/ammen/TicTacToe4x4_Classes.cpp
    ${SRC_DIR}/ammen/TicTacToe4x4_Game.cpp
    ${SRC_DIR}/ammen/UltimateTicTacToe_Classes.cpp
    ${SRC_DIR}/ammen/UltimateTicTacToe_Game.cpp

    # ========================
    # Samir 
    ${SRC_DIR}/samir/FourInARow_Classes.cpp
    ${SRC_DIR}/samir/FourInARow_Game.cpp
    ${SRC_DIR}/samir/NumericalTicTacToe_Classes.cpp
    ${SRC_DIR}/samir/NumericalTicTacToe_Game.cpp
    ${SRC_DIR}/samir/SUS_Classes.cpp
    ${SRC_DIR}/samir/SUS_Game.cpp
)

# Create executable
add_executable(BoardGameApp ${SOURCES} "include/util/colors.h")

