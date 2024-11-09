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

#
#function(install_runtime_files target)
#    get_target_property(target_link_libs ${target} INTERFACE_LINK_LIBRARIES)
#    # Set exclude list for the targets that needs to be iterated on like opengl32
#    set(_exclude_list "opengl32")
#
#    string(TOUPPER CMAKE_BUILD_TYPE build_type)
#    set(IMPORTED_TARGETS_INSTALL "")
#
#    foreach (target_name ${target_link_libs})
#        list(FIND _exclude_list "${target_name}" _exclude_index) # find target name in excluded target list
#        if (_exclude_index EQUAL -1) # if not found continue
#            get_target_property(target_type ${target_name} TYPE)
#            if(${target_type} MATCHES "(SHARED_LIBRARY|MODULE_LIBRARY)")
#                list(APPEND IMPORTED_TARGETS_INSTALL ${target_name})
#                message(STATUS "Targets include: ${target_name}")
#                # Get the list of libraries linked to the target (including shared and static libraries)
#                get_target_property(LINKED_LIBRARIES ${target_name} LINK_LIBRARIES)
#                foreach (lib ${LINKED_LIBRARIES})
#                    message(STATUS "Libraries include: ${lib}")
#                endforeach ()
#            endif ()
#        endif ()
#        unset(_target_type)
#    endforeach ()
#
#    install(IMPORTED_RUNTIME_ARTIFACTS
#            ${IMPORTED_TARGETS_INSTALL}
#            RUNTIME
#            DESTINATION ${CMAKE_INSTALL_BINDIR}
#            LIBRARY
#            DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    )

    # Get the list of libraries linked to the target (including shared and static libraries)
#    get_target_property(LINKED_LIBRARIES PnT LINK_LIBRARIES)
#    foreach (lib ${LINKED_LIBRARIES})
#        message(STATUS "Libraries include: ${lib}")
#    endforeach ()

#endfunction()

#function(get_all_dependencies target dependencies)
#    set(all_dependencies "")
#    string(TOUPPER CMAKE_BUILD_TYPE build_type)
#    # Set exclude list for the targets that need to be iterated over (like opengl32)
#    set(_exclude_list "opengl32")
#
#    # Get direct dependencies
#    get_target_property(direct_dependencies ${target} LINK_LIBRARIES)
#    if (NOT direct_dependencies)
#        set(direct_dependencies "")
#    endif()
#
#    # Get interface dependencies
#    get_target_property(interface_dependencies ${target} INTERFACE_LINK_LIBRARIES)
#    if (NOT interface_dependencies)
#        set(interface_dependencies "")
#    endif()
#
#    # Get imported dependencies
#    get_target_property(imported_dependencies ${target} IMPORTED_LOCATION)
#    if (NOT imported_dependencies)
#        set(imported_dependencies "")
#    endif()
#
#    # Get imported configuration dependencies
#    get_target_property(imported_config_dependencies ${target} IMPORTED_LOCATION_${build_type})
#    if (NOT imported_config_dependencies)
#        set(imported_config_dependencies "")
#    endif()
#
#    # Get imported link dependent libraries
#    get_target_property(imp_dependent_dependencies ${target} IMPORTED_LINK_DEPENDENT_LIBRARIES)
#    if (NOT imp_dependent_dependencies)
#        set(imp_dependent_dependencies "")
#    endif()
#
#    # Get dependent configuration libraries
#    get_target_property(dependent_config_dependencies ${target} IMPORTED_LINK_DEPENDENT_LIBRARIES_${build_type})
#    if (NOT dependent_config_dependencies)
#        set(dependent_config_dependencies "")
#    endif()
#
#    # Combine all dependencies
#    list(APPEND all_dependencies ${direct_dependencies} ${interface_dependencies}
#            ${imported_dependencies} ${imported_config_dependencies}
#            ${imp_dependent_dependencies} ${dependent_config_dependencies})
#
#    list(REMOVE_DUPLICATES all_dependencies)
#
#    # Now recurse on the direct dependencies to get their dependencies too
#    set(some_dependencies "")
#    foreach(dep IN LISTS all_dependencies)
#        list(FIND _exclude_list "${dep}" _exclude_index) # Find target name in exclude list
#        if (_exclude_index EQUAL -1) # If not found, continue
#            # Avoid recursion on already processed dependencies
#            if (NOT dep IN_LIST dependencies)
#                message(STATUS "Checking dep ${dep}")
#                get_all_dependencies(${dep} some_dependencies)  # Recursive call to get sub-dependencies
#                list(APPEND dependencies ${some_dependencies})  # Append the sub-dependencies
#            endif()
#        endif()
#    endforeach()
#
#    list(REMOVE_DUPLICATES dependencies)  # Remove any duplicates in the final list
#
#    # Pass back the list of dependencies
#    set(${dependencies} PARENT_SCOPE)
#endfunction()
#
## Usage example:
#set(all_dependencies "")
#get_all_dependencies(PnT all_dependencies)
#
## Output all dependencies (recursively)
#message("All dependencies for target 'Game' (including transitive ones):")
#foreach(dep IN LISTS all_dependencies)
#    message("${dep}")
#endforeach()


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

#    install_runtime_files(PnT)
#    get_all_dependencies(PnT dependencies)


#    message("DIRECTORIES: ${VCPKG_BIN_DIR}, ${VCPKG_DEBUG_BIN_DIR}")
#    # Specify the path to the CMake script in the project root
#    set(VCPKG_BIN_DIR "${VCPKG_BIN_DIR}")
#    set(VCPKG_DEBUG_BIN_DIR "${VCPKG_DEBUG_BIN_DIR}")
#    set(MAIN_PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/..)
#    configure_file(${MAIN_PROJECT_SOURCE_DIR}/install_dependencies.cmake.in ${CMAKE_BINARY_DIR}/install_dependencies.cmake @ONLY)
#    # Run the configured script at install time
#    install(SCRIPT ${CMAKE_BINARY_DIR}/install_dependencies.cmake)

    add_custom_command(TARGET PnT POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:PnT>
            COMMAND_EXPAND_LISTS
    )

    string(TOUPPER CMAKE_BUILD_TYPE build_type)

    message("Assimp includes  ${ASSIMP_INCLUDE_DIRS}")
#    add_custom_command(TARGET PnT POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:assimp::assimp> "${CMAKE_INSTALL_PREFIX}/bin"
#            COMMAND_EXPAND_LISTS
#    )

endif ()

if(PNT_EXPORT)
    export(EXPORT PnTTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/PnTTargets.cmake"
            NAMESPACE PnT::
    )
endif ()

