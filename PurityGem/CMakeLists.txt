# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.


# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

project(PurityEngine:PurityGem VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

include(GNUInstallDirs)

add_executable(PurityGem
        project/include/project_manager.h
        project/src/project_manager.cpp
)


# Add the core directory for the Purity library
target_include_directories(PurityGem PRIVATE
        project/include
)

target_compile_definitions(PurityGem PUBLIC PURITY_PLATFORM_WINDOWS)

# Specify the installation directory for the Game executable
install(TARGETS PurityGem DESTINATION ${CMAKE_INSTALL_BINDIR})

add_custom_command(TARGET PurityGem POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:PurityGem>
        COMMAND_EXPAND_LISTS
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

