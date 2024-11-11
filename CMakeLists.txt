# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

# Define the project name
project(Police_n_Thief VERSION 0.1.2)

# Set the C++ standard (adjust as needed)
set(CMAKE_CXX_STANDARD 17)

set(USING_PACKAGE_MANAGER_VCPKG ON CACHE BOOL "Use the package manager")

include(GNUInstallDirs)

# Ensure the directories exist before installation
file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")
file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib")
file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/include")


add_subdirectory(vendors/isle_math)
add_subdirectory(PnT)
add_subdirectory(Game)
add_subdirectory(PnTEditor)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")