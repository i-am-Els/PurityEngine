# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

cmake_minimum_required(VERSION 3.26)

project(PurityEngine:Purity VERSION 0.1.2 LANGUAGES CXX)
#project(PurityEngine VERSION 0.1.2 LANGUAGES CXX)

# Set the C++ standard/version that should be used
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

option(PURITY_INSTALL "Install Purity library" ON)
option(PURITY_EXPORT "Export Purity targets for downstream projects" ON)

option(ON_HACK "Turn on Hack Mode" OFF)
if(ON_HACK)
    add_compile_definitions(HACK_)
endif()

option(PURITY_ACTIVATE_ASSERTION "Use assertions" ON)
if (PURITY_ACTIVATE_ASSERTION)
    add_compile_definitions(PURITY_ENABLE_ASSERT)
endif()

include(GNUInstallDirs)

find_package(glfw3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(cereal CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

find_dependency(kubazip CONFIG)
find_dependency(unofficial-minizip CONFIG)
find_dependency(pugixml CONFIG REQUIRED)
find_dependency(poly2tri CONFIG)
find_dependency(polyclipping CONFIG)
find_dependency(RapidJSON CONFIG)
find_dependency(utf8cpp CONFIG)
find_dependency(ZLIB REQUIRED)

# TO ensure that targets are exported and included in Purity install
set(GLAD_INSTALL ON)
set(ASSIMP_INSTALL ON)
set(GLFW_INSTALL ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



# Create the Purity library
add_library(Purity
        SHARED
        # -----------HEADER-------------
        core/include/purity_core_pch.h
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
        assetDB/include/ref_counted.h
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
        core/include/layer_service_conc.h
        core/include/layerMask.h
        core/include/log.h
        core/include/papplication.h
        core/include/purity_core_pch.h
        core/include/purity_exceptions.h
        core/include/pobject.h
        core/include/service_locator.h
        core/include/system_finder.h
        core/include/window_purity.h
        core/include/events/keyboard_events.h
        core/include/events/mouse_events.h
        core/include/events/window_events.h
        core/include/purity.h
        #--------------------------------
        ecs/include/camera.h
        ecs/include/component.h
        ecs/include/components_behavior.h
        ecs/include/entity.h
        ecs/include/entity_base.h
        ecs/include/entity_handle.h
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
        fileIO/include/importer.h
        fileIO/include/mesh_importer.h
        #--------------------------------
        # geometry/include
        #--------------------------------
        graphics/include/buffer.h
        graphics/include/color.h
        graphics/include/renderer_service.h
        graphics/include/renderer_service_conc.h
        graphics/include/shader.h
        graphics/include/vertex_array.h
        #--------------------------------
        platform/include/imgui_opengl3_renderer.h
        #--------------------------------
        scene/include/scene.h
        #--------------------------------
        # -----------SOURCE-------------
        #--------------------------------
        assetDB/src/assetdb_service_conc.cpp
        assetDB/src/assetdb_type_strategy.cpp
        assetDB/src/assetdb_utility.cpp
        assetDB/src/assets_types.cpp
        #--------------------------------
        core/src/ecs_service_conc.cpp
        core/src/input.cpp
        core/src/layer.cpp
        core/src/layer_service_conc.cpp
        core/src/layerMask.cpp
        core/src/log.cpp
        core/src/papplication.cpp
        core/src/pobject.cpp
        core/src/system_finder.cpp
        core/src/window_purity.cpp
        #--------------------------------
        ecs/src/camera.cpp
        ecs/src/component.cpp
        ecs/src/components_behavior.cpp
        ecs/src/entity.cpp
        ecs/src/entity_handle.cpp
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
        fileIO/src/importer.cpp
        fileIO/src/mesh_importer.cpp
        #--------------------------------
        # geometry/src
        #--------------------------------
        graphics/src/buffer.cpp
        graphics/src/color.cpp
        graphics/src/renderer_service_conc.cpp
        graphics/src/shader.cpp
        graphics/src/vertex_array.cpp
        #--------------------------------
        platform/src/imgui_opengl3_renderer.cpp
        #--------------------------------
        scene/src/scene.cpp
        scene/src/scene_layer.cpp
        scene/include/scene_layer.h
        core/include/ISerializable.h
        core/src/object_registry.cpp
        core/include/object_registry.h
        core/src/serializer.cpp
        core/include/serializer.h
        core/include/serialization_macros.h
)

target_compile_definitions(Purity PUBLIC PURITY_PLATFORM_WINDOWS
        PURITY_BUILD_DLL
        PURITY_SYSTEM_FINDER
        ISLE_PLATFORM_WINDOWS
        GLFW_INCLUDE_NONE
        GLAD_DLL)

# Add the core directories for your library and dependencies
target_include_directories(Purity PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/artifacts>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/artifacts>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/assetDB/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/assetDB>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/core>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include/events>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/core/events>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ecs/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/ecs>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fileIO/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/fileIO>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/graphics/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/graphics>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/platform/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/platform>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/scene/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Purity/scene>
        # -----------------------------------------------------------------
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:vendors/isle_math/include>
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}/math>
        $<INSTALL_INTERFACE:vendors/isle_math/include/math>
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}/math/vector>
        $<INSTALL_INTERFACE:vendors/isle_math/include/math/vector>
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}/math/matrix>
        $<INSTALL_INTERFACE:vendors/isle_math/include/math/matrix>
        # -----------------------------------------------------------------
#        $<BUILD_INTERFACE:${assimp_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${Commons_INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:Commons/include>
)


target_precompile_headers(Purity PRIVATE core/include/purity_core_pch.h)

# Link against GLFW and GLEW libraries
target_link_libraries(Purity PUBLIC glfw glad::glad opengl32 IsleMath cereal::cereal GTest::gtest assimp::assimp Commons imgui::imgui)


if(PURITY_INSTALL)

    # Install header files
    install(DIRECTORY artifacts/            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/artifacts)
    install(DIRECTORY assetDB/include/      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/assetDB)
    install(DIRECTORY core/include/         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/core)
    install(DIRECTORY core/include/events/  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/core/events)
    install(DIRECTORY ecs/include/          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/ecs)
    install(DIRECTORY fileIO/include/       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/fileIO)
    install(DIRECTORY graphics/include/     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/graphics)
    install(DIRECTORY platform/include/     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/platform)
    install(DIRECTORY scene/include/        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Purity/scene)


    # Install the Purity library (DLL or shared library)
    install(TARGETS Purity
            EXPORT PurityTargets             # Exported target for the package
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # DLLs on Windows
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # Shared libraries on UNIX
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # Static libraries, if applicable
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Export the targets to a file
    install(EXPORT PurityTargets
            FILE PurityTargets.cmake
            NAMESPACE Purity::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Purity
    )

    # Package configuration
    include(CMakePackageConfigHelpers)

    # Configure the main PurityConfig.cmake file from a template
    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/PurityConfig.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/PurityConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Purity)

    # Write version file for the package
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/PurityConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
    )

    # Install the config and version files
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/PurityConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/PurityConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Purity
    )

    add_custom_command(TARGET Purity POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:Purity>
            COMMAND_EXPAND_LISTS
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )


    string(TOUPPER CMAKE_BUILD_TYPE build_type)
    
    message("Assimp includes  ${ASSIMP_INCLUDE_DIRS}")
    add_custom_command(TARGET Purity POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${VCPKG_BIN_DIR}/pugixml.dll"
            "${CMAKE_INSTALL_PREFIX}/bin"
    )
    
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET Purity POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VCPKG_DEBUG_BIN_DIR}/zlibd1.dll"
                "${CMAKE_INSTALL_PREFIX}/bin"
        )
    else ()
        add_custom_command(TARGET Purity POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VCPKG_BIN_DIR}/zlib1.dll"
                "${CMAKE_INSTALL_PREFIX}/bin"
        )
    endif ()
endif ()

if(PURITY_EXPORT)
    export(EXPORT PurityTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/PurityTargets.cmake"
            NAMESPACE Purity::
    )
endif ()

