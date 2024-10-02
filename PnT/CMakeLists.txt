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

option(ON_HACK "Turn on Hack Mode" OFF)
if(ON_HACK)
    add_compile_definitions(HACK_)
endif()

option(PNT_ACTIVATE_ASSERTION "Use assertions" ON)
if (PNT_ACTIVATE_ASSERTION)
    add_compile_definitions(PNT_ENABLE_ASSERT)
endif()

add_subdirectory(vendors/isle_math)

# Create the PnT library
add_library(PnT SHARED
        core/include/pnt_core_pch.h
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
        renderer/src/render_system_conc.cpp
        renderer/include/render_system_conc.h
        ecs/include/components_behavior.h
        ecs/src/renderer.cpp
        ecs/include/renderer.h
        ecs/include/renderer.h
        ecs/include/renderer.h
        ecs/include/renderer.h
        core/include/linkedList.h
        core/include/papplication.h
        core/src/papplication.cpp
        ecs/src/scripting.cpp
        ecs/include/scripting.h
        renderer/include/buffer.h
        renderer/src/buffer.cpp
        ecs/include/isystems.h
        core/include/iservices.h
        core/include/service_base.h
        core/include/service_locator.h
        renderer/include/render_system.h
        geometry/include/mesh_system_conc.h
        geometry/src/mesh_system_conc.cpp
        geometry/include/mesh_system.h
        ecs/include/ecs_service.h
        ecs/include/ecs_service_conc.h
        io/src/fileio.cpp
        io/include/fileio.h
        ecs/src/components_behavior.cpp
        ecs/src/ecs_service_conc.cpp
        scene/include/transform_system.h
        scene/src/transform_system_conc.cpp
        scene/include/transform_system_conc.h
        ecs/include/entity_base.h
        core/include/core_macros.h
        core/include/window_pnt.h
        core/include/system_finder.h
        core/src/system_finder.cpp
        assets/src/assetdb_service_conc.cpp
        assets/include/assetdb_service_conc.h
        assets/include/assetdb_service.h
        io/include/handle_base.h
        core/src/pobject.cpp
        core/include/pobject.h
        assets/include/assetdb_enums.h
        assets/include/assetdb_query_specs.h
        assets/include/assetdb_type_strategy.h
        assets/src/assetdb_type_strategy.cpp
        assets/src/assetdb_utility.cpp
        assets/include/assetdb_utility.h
        core/include/pnt_exceptions.h
        assets/src/assets_types.cpp
        assets/include/assets_types.h
        assets/src/uuid.cpp
        assets/include/uuid.h
        scene/src/scene.cpp
        scene/include/scene.h
        ecs/include/tag_comp.h
        ecs/src/id_comp.cpp
        ecs/include/id_comp.h
        ecs/src/tag_comp.cpp
        ecs/include/reg_system.h
        ecs/src/entity_registry.cpp
        ecs/include/entity_registry.h
        ecs/src/reg_system_conc.cpp
        ecs/include/reg_system_conc.h
        core/include/events.h
        core/include/events/keyboard_events.h
        core/include/events/mouse_events.h
        core/include/events/window_events.h
        core/include/entry.h
        core/include/layer_service.h
        core/include/layer_service.h
        io/src/mesh_importer.cpp
        io/include/mesh_importer.h
)

# Add the core directories for your library and dependencies
target_include_directories(PnT PUBLIC
        artifacts
        assets/include
        core/include
        core/include/events
        ecs/include
        io/include
        geometry/include
        renderer/include
        scene/include
        vendors/GLAD/include
)

target_compile_definitions(PnT PUBLIC PNT_PLATFORM_WINDOWS PNT_BUILD_DLL ISLE_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

# Link against GLFW and GLEW libraries
target_link_libraries(PnT PUBLIC glad glfw opengl32 islemath assimp)

target_precompile_headers(PnT PRIVATE core/include/pnt_core_pch.h)

include(FetchContent)

#
## Set the FetchContent cache behavior to avoid re-downloading
#set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# Fetch GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
FetchContent_MakeAvailable(glad)

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG        v5.4.3  # Replace with the version/tag you want
)
FetchContent_MakeAvailable(assimp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Install header files to shared/core directory
#install(FILES ${HEADERS} DESTINATION ${CMAKE_SOURCE_DIR}/shared/include)

#option(MSVC_DEBUG_BUILD "Debug build with Visual Studio" ON)
#
#set(GLAD_DLL_PATH $<TARGET_FILE_DIR:glad>)
#set(GLFW_DLL_PATH $<TARGET_FILE_DIR:glfw>)
#
#if(MSVC_DEBUG_BUILD)
#    # Copy the DLL to the executable directory after build
#    add_custom_command(TARGET PnT POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${GLAD_DLL_PATH}/glad.dll"
#            $<TARGET_FILE_DIR:PnT>)
#    add_custom_command(TARGET PnT POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${GLFW_DLL_PATH}/glfw3.dll"
#            $<TARGET_FILE_DIR:PnT>)
#endif()