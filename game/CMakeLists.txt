# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.26)
project(Police_n_Thief)

set(CMAKE_CXX_STANDARD 17)

option(MSVC_DEBUG_BUILD "Debug build with Visual Studio" ON)

# Define your source files in src/
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(Game ${SOURCES}
        src/application.cpp
        src/application.h
        src/quad_comp.cpp
        src/quad_comp.h)

# Add the core directory for the PnT library
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/core)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(Game PRIVATE PnT)

target_compile_definitions(Game PUBLIC PNT_PLATFORM_WINDOWS)

# Path to the DLL in the build directory
set(PNT_DLL_PATH $<TARGET_FILE_DIR:PnT>)
set(GLAD_DLL_PATH $<TARGET_FILE_DIR:glad>)
set(GLFW_DLL_PATH $<TARGET_FILE_DIR:glfw>)

if(MSVC_DEBUG_BUILD)
    # Copy the DLL to the executable directory after build
    add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PNT_DLL_PATH}/PnT.dll"
            $<TARGET_FILE_DIR:Game>)
    add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLAD_DLL_PATH}/glad.dll"
            $<TARGET_FILE_DIR:Game>)
    add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLFW_DLL_PATH}/glfw3.dll"
            $<TARGET_FILE_DIR:Game>)
else ()
    # Copy the DLL to the executable directory after build
    add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PNT_DLL_PATH}/libPnT.dll"
            $<TARGET_FILE_DIR:Game>)
    add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLAD_DLL_PATH}/libglad.dll"
            $<TARGET_FILE_DIR:Game>)
    add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLFW_DLL_PATH}/glfw3.dll"
            $<TARGET_FILE_DIR:Game>)
endif()