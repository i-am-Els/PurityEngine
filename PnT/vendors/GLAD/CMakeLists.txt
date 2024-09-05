# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.26)
project(Police_n_Thief)

set(CMAKE_CXX_STANDARD 17)

# Build the math src to static library
add_library(
        glad
        SHARED
        include/glad/glad.h
        src/glad.c
)

target_include_directories(glad PUBLIC include)
