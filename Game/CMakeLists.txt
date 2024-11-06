# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

cmake_minimum_required(VERSION 3.26)

#project(Game VERSION 0.1.2 LANGUAGES CXX)
project(Police_n_Thief VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

option(MSVC_DEBUG_BUILD "Debug build with Visual Studio" ON)

# Define your source files in src/
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(Game ${SOURCES}
        src/application.cpp
        src/application.h
        src/quad_comp.cpp
        src/quad_comp.h)

# Add the core directory for the PnT library
#target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/core)

find_package(PnT CONFIG REQUIRED)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(Game PRIVATE PnT::PnT)

target_compile_definitions(Game PUBLIC PNT_PLATFORM_WINDOWS)

## Path to the DLL in the build directory
#set(PNT_DLL_PATH $<TARGET_FILE_DIR:PnT>)
#set(GLAD_DLL_PATH $<TARGET_FILE_DIR:glad>)
#set(GLFW_DLL_PATH $<TARGET_FILE_DIR:glfw>)
#set(ASSIMP_DLL_PATH $<TARGET_FILE_DIR:assimp>)
#set(ISLEMATH_DLL_PATH $<TARGET_FILE_DIR:islemath>)
#
#if(MSVC_DEBUG_BUILD)
#    # Copy the DLL to the executable directory after build
#    add_custom_command(TARGET Game POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${PNT_DLL_PATH}/PnT.dll"
#            "${GLAD_DLL_PATH}/glad.dll"
#            "${GLFW_DLL_PATH}/glfw3.dll"
#            "${ASSIMP_DLL_PATH}/assimp-vc143-mt.dll"
#            "${ISLEMATH_DLL_PATH}/islemath.dll"
#            $<TARGET_FILE_DIR:Game>)
#
#else ()
#    # Copy the DLL to the executable directory after build
#    add_custom_command(TARGET Game POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${PNT_DLL_PATH}/libPnT.dll"
#            "${GLAD_DLL_PATH}/libglad.dll"
#            "${GLFW_DLL_PATH}/glfw3.dll"
#            "${ASSIMP_DLL_PATH}/libassimp-5.dll"
#            "${ISLEMATH_DLL_PATH}/libislemath.dll"
#            $<TARGET_FILE_DIR:Game>)
#endif()