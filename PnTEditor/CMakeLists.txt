# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)
project(Police_n_Thief)

set(CMAKE_CXX_STANDARD 17)


# Add tasks subprojects
add_executable(PnTEditor gui/editor.cpp gui/editor.h)