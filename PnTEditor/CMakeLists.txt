# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.


# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

project(Police_n_Thief:PnTEditor VERSION 0.1.2 LANGUAGES CXX)
#project(Police_n_Thief VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

include(GNUInstallDirs)

add_executable(PnTEditor
        gui/src/editor.cpp
        gui/include/editor.h
        project/src/project_manager.cpp
        project/include/project_manager.h
        gui/src/p_editor_application.cpp
        gui/include/p_editor_application.h
)


# Add the core directory for the PnT library
target_include_directories(PnTEditor PRIVATE
#        ${CMAKE_SOURCE_DIR}/PnT/core
        core/include
        gui/include
        project/include
#        $<BUILD_INTERFACE:${PnT_INCLUDE_DIRS}>
#        $<BUILD_INTERFACE:${PnT_INCLUDE_DIRS}/core>
)

add_dependencies(PnTEditor IsleMath PnT)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(PnTEditor PRIVATE PnT)

target_compile_definitions(PnTEditor PUBLIC PNT_PLATFORM_WINDOWS)

# Specify the installation directory for the Game executable
install(TARGETS PnTEditor DESTINATION ${CMAKE_INSTALL_BINDIR})

add_custom_command(TARGET PnTEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:PnTEditor>
        COMMAND_EXPAND_LISTS
)

