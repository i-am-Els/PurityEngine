# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.26)
project(Police_n_Thief)

# Set the C++ standard/version that should be used
set(CMAKE_CXX_STANDARD 17)

# Define your source files in src/
file(GLOB SOURCES "src/*.cpp")

# Create the PnT library
add_library(PnT STATIC ${SOURCES})

# Add the include directories for your library and dependencies
target_include_directories(PnT PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(PnT PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include/math)
target_include_directories(PnT PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include/renderer)
target_include_directories(PnT PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLEW/include)
target_include_directories(PnT PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLFW/include)

target_link_directories(PnT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLEW/lib)
target_link_directories(PnT PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLFW/lib)

# Link against GLFW and GLEW libraries
target_link_libraries(PnT PRIVATE glew32s glfw3 opengl32)

# Specify header files to include (all .h files in the include directory)
file(GLOB_RECURSE HEADER_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLEW/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLFW/include/*.h")

# Set the output directory for the library
set_target_properties(PnT PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/lib  # Set the desired output directory here
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/bin
)


# Install header files to shared/include directory
install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/shared/include)
