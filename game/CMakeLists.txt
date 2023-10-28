# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.26)
project(Police_n_Thief)


set(CMAKE_CXX_STANDARD 17)

# Define your source files in src/
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(Game ${SOURCES})

# Add the include directory for the PnT library
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/include)
#target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/vendors/GLEW/include)
#target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/vendors/GLFW/include)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(Game PRIVATE PnT)
