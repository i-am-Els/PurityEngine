# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

# Append install directories to CMAKE_PREFIX_PATH to locate generated targets
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/IsleMath_install")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/PnT_install")

# Define the project name
project(Police_n_Thief VERSION 0.1.2)


# Set the C++ standard (adjust as needed)
set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

# Add IsleMath as a standalone project
ExternalProject_Add(IsleMath
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendors/isle_math
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/IsleMath_install
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        BUILD_ALWAYS TRUE
)


# Add PnT as another standalone project, with IsleMath as a dependency
ExternalProject_Add(PnT
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/PnT
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/PnT_install
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        BUILD_ALWAYS TRUE
        DEPENDS IsleMath  # Make sure PnT builds after IsleMath
)


# Add PnTEditor and set it to depend on PnT
ExternalProject_Add(PnTEditor
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/PnTEditor
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/PnTEditor_install
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        BUILD_ALWAYS TRUE
        DEPENDS PnT  # Ensure PnT builds first
)

# Add Game and set it to depend on IsleMath and PnT
ExternalProject_Add(Game
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/Game
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/Game_install
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        BUILD_ALWAYS TRUE
        DEPENDS IsleMath PnT # Ensures IsleMath then PnT builds first
)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message("Considered : ${IsleMath_CONSIDERED_CONFIGS}")
