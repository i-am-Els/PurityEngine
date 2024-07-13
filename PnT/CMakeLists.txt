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
file(GLOB_RECURSE SOURCES "*.cpp")

# Specify header files to core (all .h files in the core directory)
file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/core/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLEW/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLFW/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendors/isle_math/include/*.h"
)

# Create the PnT library
add_library(PnT STATIC
        ${SOURCES}
        ${HEADERS}
        ecs/src/camera.cpp
        ecs/include/camera.h
        ecs/src/entity.cpp
        ecs/include/entity.h
        ecs/include/component.h
        ecs/src/component.cpp
        artifacts/data_hash_table.h
        renderer/include/color.h
        renderer/src/color.cpp
        ecs/include/mesh.h
        ecs/include/transform_ecs.h
        ecs/src/transform_ecs.cpp
        ecs/src/mesh.cpp
        artifacts/tags.h
        renderer/src/opengl_renderer.cpp
        renderer/include/opengl_renderer.h
        ecs/include/IEntity.h
        ecs/src/renderer.cpp
        ecs/include/renderer.h
        ecs/include/renderer.h
        ecs/include/renderer.h
        ecs/include/renderer.h
        core/linkedList.h
        core/application.h
        ecs/src/scripting.cpp
        ecs/include/scripting.h
        renderer/include/buffer.h
        ecs/include/isystems.h
        core/iservices.h
        core/service_base.h
        core/service_locator.h
        renderer/include/render_service.h
)

# Add the core directories for your library and dependencies
target_include_directories(PnT PUBLIC
        artifacts
        core
        ecs/include
        io/include
        renderer/include
        vendors/GLEW/include
        vendors/GLFW/include
        vendors/GLM
        vendors/isle_math/include
        vendors/isle_math/include/math
        vendors/isle_math/include/math/matrix
        vendors/isle_math/include/math/vector
)

target_link_directories(PnT PUBLIC
        vendors/GLEW/lib
        vendors/GLFW/lib
        vendors/isle_math/lib
)

target_compile_definitions(PnT PUBLIC GLEW_STATIC ISLE_PLATFORM_WINDOWS)

# Link against GLFW and GLEW libraries
target_link_libraries(PnT PUBLIC glew32s glfw3 opengl32 islemath)

# Set the output directory for the library
set_target_properties(PnT PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/lib  # Set the desired output directory here
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/shared/lib
)

# Install header files to shared/core directory
install(FILES ${HEADERS} DESTINATION ${CMAKE_SOURCE_DIR}/shared/include)

### ISLE MATH definitions
target_precompile_headers(PnT PUBLIC
        vendors/isle_math/include/isle_pch.h
)
