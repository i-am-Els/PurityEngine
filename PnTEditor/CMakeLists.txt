# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.


# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

#project(PnTEditor VERSION 0.1.2 LANGUAGES CXX)
project(Police_n_Thief VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

option(MSVC_DEBUG_BUILD "Debug build with Visual Studio" ON)

message("Message-- CMAKE VAR: ${PnT_INCLUDE_DIRS}")

# Add tasks subprojects
add_executable(PnTEditor
        gui/src/editor.cpp
        gui/include/editor.h
        project/src/project_manager.cpp
        project/include/project_manager.h
        gui/src/p_editor_application.cpp
        gui/include/p_editor_application.h)


# Add the core directory for the PnT library
target_include_directories(PnTEditor PRIVATE
#        ${CMAKE_SOURCE_DIR}/PnT/core
        core/include
        gui/include
        project/include
        $<BUILD_INTERFACE:${PnT_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${PnT_INCLUDE_DIRS}/core>
)

find_package(PnT CONFIG REQUIRED)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(PnTEditor PRIVATE PnT::PnT)

target_compile_definitions(PnTEditor PUBLIC PNT_PLATFORM_WINDOWS)

## Path to the DLL in the build directory
#set(PNT_DLL_PATH $<TARGET_FILE_DIR:PnT>)
#set(GLAD_DLL_PATH $<TARGET_FILE_DIR:glad>)
#set(GLFW_DLL_PATH $<TARGET_FILE_DIR:glfw>)
#set(ASSIMP_DLL_PATH $<TARGET_FILE_DIR:assimp>)
#set(ISLEMATH_DLL_PATH $<TARGET_FILE_DIR:islemath>)

#if(MSVC_DEBUG_BUILD)
#    # Copy the DLL to the executable directory after build
#    add_custom_command(TARGET PnTEditor POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${PNT_DLL_PATH}/PnT.dll"
#            "${GLAD_DLL_PATH}/glad.dll"
#            "${GLFW_DLL_PATH}/glfw3.dll"
#            "${ASSIMP_DLL_PATH}/assimp-vc143-mt.dll"
#            "${ISLEMATH_DLL_PATH}/islemath.dll"
#            $<TARGET_FILE_DIR:PnTEditor>)
#
#else ()
#    # Copy the DLL to the executable directory after build
#    add_custom_command(TARGET PnTEditor POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${PNT_DLL_PATH}/libPnT.dll"
#            "${GLAD_DLL_PATH}/libglad.dll"
#            "${GLFW_DLL_PATH}/glfw3.dll"
#            "${ASSIMP_DLL_PATH}/libassimp-5.dll"
#            "${ISLEMATH_DLL_PATH}/libislemath.dll"
#            $<TARGET_FILE_DIR:PnTEditor>)
#endif()