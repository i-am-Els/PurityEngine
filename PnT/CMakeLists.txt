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
        # ----------- HEADER ------------
        core/include/pnt_core_pch.h
        #--------------------------------
        artifacts/data_hash_table.h
        artifacts/tags.h
        #--------------------------------
        assetDB/include/assetdb_enums.h
        assetDB/include/assetdb_query_specs.h
        assetDB/include/assetdb_service_conc.h
        assetDB/include/assetdb_type_strategy.h
        assetDB/include/assetdb_utility.h
        assetDB/include/assets_types.h
        #--------------------------------
        core/include/assetdb_service.h
        core/include/core_macros.h
        core/include/ecs_service.h
        core/include/ecs_service_conc.h
        core/include/entry.h
        core/include/events.h
        core/include/input.h
        core/include/input_def.h
        core/include/iservices.h
        core/include/layer.h
        core/include/layer_service.h
        core/include/layerMask.h
        core/include/log.h
        core/include/papplication.h
        core/include/pnt_core_pch.h
        core/include/pnt_exceptions.h
        core/include/pobject.h
        core/include/service_base.h
        core/include/service_locator.h
        core/include/system_finder.h
        core/include/uuid.h
        core/include/window_pnt.h
        core/include/events/keyboard_events.h
        core/include/events/mouse_events.h
        core/include/events/window_events.h
        core/pnt.h
        #--------------------------------
        ecs/include/camera.h
        ecs/include/component.h
        ecs/include/components_behavior.h
        ecs/include/entity.h
        ecs/include/entity_base.h
        ecs/include/entity_registry.h
        ecs/include/id_comp.h
        ecs/include/isystems.h
        ecs/include/mesh.h
        ecs/include/mesh_system_conc.h
        ecs/include/reg_system.h
        ecs/include/reg_system_conc.h
        ecs/include/render_system.h
        ecs/include/render_system_conc.h
        ecs/include/renderer.h
        ecs/include/scripting.h
        ecs/include/tag_comp.h
        ecs/include/transform_ecs.h
        ecs/include/transform_system.h
        ecs/include/transform_system_conc.h
        #--------------------------------
        fileIO/include/fileio.h
        fileIO/include/handle_base.h
        fileIO/include/mesh_importer.h
        #--------------------------------
        # geometry/include
        #--------------------------------
        graphics/include/buffer.h
        graphics/include/color.h
        graphics/include/shader.h
        graphics/include/vertex_array.h
        #--------------------------------
        scene/include/scene.h
        #--------------------------------
        #--------------------------------
        # ----------- SOURCE ------------
        #--------------------------------
        assetDB/src/assetdb_service_conc.cpp
        assetDB/src/assetdb_type_strategy.cpp
        assetDB/src/assetdb_utility.cpp
        assetDB/src/assets_types.cpp
        assetDB/src/uuid.cpp
        #--------------------------------
        core/src/ecs_service_conc.cpp
        core/src/input.cpp
        core/src/layer.cpp
        core/src/layerMask.cpp
        core/src/log.cpp
        core/src/papplication.cpp
        core/src/pobject.cpp
        core/src/system_finder.cpp
        core/src/window_pnt.cpp
        #--------------------------------
        ecs/src/camera.cpp
        ecs/src/component.cpp
        ecs/src/components_behavior.cpp
        ecs/src/entity.cpp
        ecs/src/entity_registry.cpp
        ecs/src/id_comp.cpp
        ecs/src/mesh.cpp
        ecs/src/mesh_system_conc.cpp
        ecs/src/reg_system_conc.cpp
        ecs/src/render_system_conc.cpp
        ecs/src/renderer.cpp
        ecs/src/scripting.cpp
        ecs/src/tag_comp.cpp
        ecs/src/transform_ecs.cpp
        ecs/src/transform_system_conc.cpp
        #--------------------------------
        fileIO/src/fileio.cpp
        fileIO/src/mesh_importer.cpp
        #--------------------------------
        # geometry/src
        #--------------------------------
        graphics/src/buffer.cpp
        graphics/src/color.cpp
        graphics/src/shader.cpp
        graphics/src/vertex_array.cpp
        #--------------------------------
        scene/src/scene.cpp
)

# Add the core directories for your library and dependencies
target_include_directories(PnT PUBLIC
        artifacts
        assetDB/include
        core/include
        core/include/events
        ecs/include
        fileIO/include
        graphics/include
        scene/include
        vendors/isle_math/include
)

target_compile_definitions(PnT PUBLIC PNT_PLATFORM_WINDOWS PNT_BUILD_DLL ISLE_PLATFORM_WINDOWS GLFW_INCLUDE_NONE)

# Link against GLFW and GLEW libraries
target_link_libraries(PnT PUBLIC glad glfw opengl32 islemath assimp)

target_precompile_headers(PnT PRIVATE core/include/pnt_core_pch.h)

include(FetchContent)

## Set the FetchContent cache behavior to avoid re-downloading
#set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# Fetch GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)
#if(NOT glfw_POPULATED)
    FetchContent_MakeAvailable(glfw)
#endif ()


FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)
#if(NOT glad_POPULATED)
    FetchContent_MakeAvailable(glad)
#endif ()


FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG       v5.4.3  # Replace with the version/tag you want
)
#if (NOT assimp_POPULATED)
    FetchContent_MakeAvailable(assimp)
#endif()


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