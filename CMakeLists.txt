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
    ${SRC_DIR}/XO_Classes.cpp
)

# Create executable
add_executable(BoardGameApp ${SOURCES})
