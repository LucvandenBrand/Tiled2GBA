cmake_minimum_required(VERSION 3.9)
project(Tiled2GBA)

# Compilation settings.
set(CMAKE_CXX_STANDARD 17)

# Build Tiled2GBA
file(GLOB_RECURSE PROJECT_SOURCES src/*.c src/*.cpp src/*.h src/*.hpp src/*.inl)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_dependencies(${PROJECT_NAME} gbfs padbin)

# Build additional tools.
file(GLOB_RECURSE GBFS_SOURCES tools/gbfs/*.c tools/gbfs/*.h)
add_executable(gbfs ${GBFS_SOURCES})

file(GLOB_RECURSE PADBIN_SOURCES tools/padbin/*.c tools/padbin/*.h)
add_executable(padbin ${PADBIN_SOURCES})

set(DEVKITARM /opt/devkitpro/devkitARM)
if(EXISTS ${DEVKITARM})
    set(MAPVIEWER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/mapViewer)
    set(MAPVIEWER mapViewer.gba)
    add_custom_target(
            ${MAPVIEWER}
            COMMAND make
            WORKING_DIRECTORY ${MAPVIEWER_DIR}
            )
    add_dependencies(${PROJECT_NAME} ${MAPVIEWER})
    configure_file(${MAPVIEWER_DIR}/${MAPVIEWER} ${MAPVIEWER} COPYONLY)
else()
    message(STATUS "No DevkitARM found in ${DEVKITARM}, skipping mapViewer build")
endif()