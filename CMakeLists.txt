cmake_minimum_required(VERSION 3.15)
project(BoardGameApp)
# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# header files
include_directories(include)

# source files
set(SOURCES
    src/Main.cpp
    src/XO_Classes.cpp
)

# create executable
add_executable(BoardGameApp ${SOURCES})
