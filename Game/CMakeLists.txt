# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

cmake_minimum_required(VERSION 3.26)

project(Game VERSION 0.1.2 LANGUAGES CXX)
#project(Police_n_Thief VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_executable(Game
        src/application.cpp
        src/application.h
        src/quad_comp.cpp
        src/quad_comp.h
)

# Add the core directory for the PnT library
#target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/core)

find_package(PnT CONFIG REQUIRED)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(Game PRIVATE PnT::PnT)

target_compile_definitions(Game PUBLIC PNT_PLATFORM_WINDOWS)

# Specify the installation directory for the Game executable
install(TARGETS Game DESTINATION ${CMAKE_INSTALL_BINDIR})

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:Game>
        COMMAND_EXPAND_LISTS
)

