# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.26)
project(Police_n_Thief)

set(CMAKE_CXX_STANDARD 17)

# Define your source files in src/
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(Game ${SOURCES}
        src/application.cpp
        src/application.h)

# Add the core directory for the PnT library
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/core)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(Game PRIVATE PnT)

# Path to the DLL in the build directory
set(DLL_PATH $<TARGET_FILE_DIR:glad>)

# Copy the DLL to the executable directory after build
add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DLL_PATH}/libglad.dll"
        $<TARGET_FILE_DIR:Game>)