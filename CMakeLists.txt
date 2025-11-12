cmake_minimum_required(VERSION 3.15)
project(BoardGameApp)

#  C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
#Header files
include_directories(${INCLUDE_DIR})

# Src files
set(SOURCES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Menu.cpp
    # ========================
    ${SRC_DIR}/XO_Classes.cpp
    ${SRC_DIR}/Connect4_Classes.cpp
    ${SRC_DIR}/SUS_Classes.cpp

    # ======================== 
    ${SRC_DIR}/XO_Game.cpp
    ${SRC_DIR}/SUS_Game.cpp
    ${SRC_DIR}/Connect4_Game.cpp

)

# Create executable
add_executable(BoardGameApp ${SOURCES})

