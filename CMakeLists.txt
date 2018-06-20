cmake_minimum_required(VERSION 3.9)
project(Tiled2GBA)

# Source location.
file(GLOB_RECURSE SOURCES src/*.c src/*.cpp src/*.h src/*.hpp src/*.inl)

# Compilation settings.
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} ${SOURCES})
