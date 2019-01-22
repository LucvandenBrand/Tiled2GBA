cmake_minimum_required(VERSION 3.9)
project(Tiled2GBA)

# Compilation settings.
set(CMAKE_CXX_STANDARD 17)

# Build Tiled2GBA
file(GLOB_RECURSE PROJECT_SOURCES src/*.c src/*.cpp src/*.h src/*.hpp src/*.inl)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
