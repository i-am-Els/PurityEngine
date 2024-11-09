# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

cmake_minimum_required(VERSION 3.26)

project(PnT VERSION 0.1.2 LANGUAGES CXX)
#project(Police_n_Thief VERSION 0.1.2 LANGUAGES CXX)

# Set the C++ standard/version that should be used
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

option(PNT_INSTALL "Install PnT library" ON)
option(PNT_EXPORT "Export PnT targets for downstream projects" ON)

option(ON_HACK "Turn on Hack Mode" OFF)
if(ON_HACK)
    add_compile_definitions(HACK_)
endif()

option(PNT_ACTIVATE_ASSERTION "Use assertions" ON)
if (PNT_ACTIVATE_ASSERTION)
    add_compile_definitions(PNT_ENABLE_ASSERT)
endif()

include(GNUInstallDirs)

find_package(IsleMath CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(cereal CONFIG REQUIRED)

# TO ensure that targets are exported and included in PnT install
set(GLAD_INSTALL ON)
set(ASSIMP_INSTALL ON)
set(GLFW_INSTALL ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



# Create the PnT library
add_library(PnT
        SHARED
        # -----------HEADER-------------
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
        core/include/pnt.h
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
        # -----------SOURCE-------------
        #--------------------------------
        assetDB/src/assetdb_service_conc.cpp
        assetDB/src/assetdb_type_strategy.cpp
        assetDB/src/assetdb_utility.cpp
        assetDB/src/assets_types.cpp
        #--------------------------------
        core/src/uuid.cpp
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

target_compile_definitions(PnT PUBLIC PNT_PLATFORM_WINDOWS PNT_BUILD_DLL ISLE_PLATFORM_WINDOWS GLFW_INCLUDE_NONE GLAD_DLL)

# Add the core directories for your library and dependencies
target_include_directories(PnT PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/artifacts>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/artifacts>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/assetDB/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/assetDB>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/core>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include/events>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/core/events>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ecs/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/ecs>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fileIO/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/fileIO>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/graphics/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/graphics>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/scene/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/PnT/scene>
        # -----------------------------------------------------------------
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}/math>
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}/math/vector>
        $<BUILD_INTERFACE:${IsleMath_INCLUDE_DIRS}/math/matrix>
        # -----------------------------------------------------------------
#        $<BUILD_INTERFACE:${assimp_INCLUDE_DIRS}>
)


target_precompile_headers(PnT PRIVATE core/include/pnt_core_pch.h)

# Link against GLFW and GLEW libraries
target_link_libraries(PnT PUBLIC glfw glad::glad opengl32 IsleMath::IsleMath cereal::cereal GTest::gtest assimp::assimp)


if(PNT_INSTALL)

    # Install header files
    install(DIRECTORY artifacts/            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/artifacts)
    install(DIRECTORY assetDB/include/      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/assetDB)
    install(DIRECTORY core/include/         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/core)
    install(DIRECTORY core/include/events/  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/core/events)
    install(DIRECTORY ecs/include/          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/ecs)
    install(DIRECTORY fileIO/include/       DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/fileIO)
    install(DIRECTORY graphics/include/     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/graphics)
    install(DIRECTORY scene/include/        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PnT/scene)


    # Install the PnT library (DLL or shared library)
    install(TARGETS PnT
            EXPORT PnTTargets             # Exported target for the package
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # DLLs on Windows
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # Shared libraries on UNIX
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # Static libraries, if applicable
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Export the targets to a file
    install(EXPORT PnTTargets
            FILE PnTTargets.cmake
            NAMESPACE PnT::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PnT
    )

    # Package configuration
    include(CMakePackageConfigHelpers)

    # Configure the main PnTConfig.cmake file from a template
    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/PnTConfig.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/PnTConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PnT)

    # Write version file for the package
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/PnTConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
    )

    # Install the config and version files
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/PnTConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/PnTConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PnT
    )

    add_custom_command(TARGET PnT POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:PnT>
            COMMAND_EXPAND_LISTS
    )

    string(TOUPPER CMAKE_BUILD_TYPE build_type)

    message("Assimp includes  ${ASSIMP_INCLUDE_DIRS}")
    add_custom_command(TARGET PnT POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${VCPKG_BIN_DIR}/pugixml.dll"
            "${CMAKE_INSTALL_PREFIX}/bin"
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET PnT POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VCPKG_DEBUG_BIN_DIR}/zlibd1.dll"
                "${CMAKE_INSTALL_PREFIX}/bin"
        )
    else ()
        add_custom_command(TARGET PnT POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${VCPKG_BIN_DIR}/zlib1.dll"
                "${CMAKE_INSTALL_PREFIX}/bin"
        )
    endif ()

endif ()

if(PNT_EXPORT)
    export(EXPORT PnTTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/PnTTargets.cmake"
            NAMESPACE PnT::
    )
endif ()

