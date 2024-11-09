# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

cmake_minimum_required(VERSION 3.26)

project(Game VERSION 0.1.2 LANGUAGES CXX)
#project(Police_n_Thief VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_executable(Game
        src/application.cpp
        src/application.h
        src/quad_comp.cpp
        src/quad_comp.h
)

# Add the core directory for the PnT library
#target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/PnT/core)

find_package(PnT CONFIG REQUIRED)

# Link against the PnT library (assuming it's built in a sibling directory)
target_link_libraries(Game PRIVATE PnT::PnT)

target_compile_definitions(Game PUBLIC PNT_PLATFORM_WINDOWS)

#if(MSVC)
#    # Copy the DLL to the executable directory after build
#    add_custom_command(TARGET Game POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${CMAKE_INSTALL_PREFIX}/bin/PnT.dll"
#            "${CMAKE_INSTALL_PREFIX}/bin/IsleMath.dll"
##            "${VCPKG_BIN_DIR}/glfw3.dll"
#            $<TARGET_FILE_DIR:Game>)
##    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
##        add_custom_command(TARGET Game POST_BUILD
##                COMMAND ${CMAKE_COMMAND} -E copy_if_different
##                "${VCPKG_DEBUG_BIN_DIR}/assimp-vc143-mtd.dll"
##                $<TARGET_FILE_DIR:Game>)
##    else()
##        add_custom_command(TARGET Game POST_BUILD
##                COMMAND ${CMAKE_COMMAND} -E copy_if_different
##                "${VCPKG_BIN_DIR}/assimp-vc143-mt.dll"
##                $<TARGET_FILE_DIR:Game>)
##    endif()
#else()
#    # Copy the DLL to the executable directory after build
#    add_custom_command(TARGET Game POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${CMAKE_INSTALL_PREFIX}/bin/libPnT.dll"
#            "${CMAKE_INSTALL_PREFIX}/bin/libIsleMath.dll"
##            "${VCPKG_BIN_DIR}/libglfw3.dll"
#            $<TARGET_FILE_DIR:Game>)
#
##    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
##        add_custom_command(TARGET Game POST_BUILD
##                COMMAND ${CMAKE_COMMAND} -E copy_if_different
##                "${VCPKG_DEBUG_BIN_DIR}/libassimp-5d.dll"
##                $<TARGET_FILE_DIR:Game>)
##    else()
##        add_custom_command(TARGET Game POST_BUILD
##                COMMAND ${CMAKE_COMMAND} -E copy_if_different
##                "${VCPKG_BIN_DIR}/libassimp-5.dll"
##                $<TARGET_FILE_DIR:Game>)
##    endif()
#endif()

# Specify the installation directory for the Game executable
install(TARGETS Game DESTINATION ${CMAKE_INSTALL_BINDIR})

add_custom_command(TARGET Game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:Game>
        COMMAND_EXPAND_LISTS
)

#message("DIRECTORIES: ${VCPKG_BIN_DIR}, ${VCPKG_DEBUG_BIN_DIR}")
#
# Add runtime dependency gathering and installation for Game
## Specify the path to the CMake script in the project root
#set(VCPKG_BIN_DIR "${VCPKG_BIN_DIR}")
#set(VCPKG_DEBUG_BIN_DIR "${VCPKG_DEBUG_BIN_DIR}")
#set(MAIN_PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/..)
#configure_file(${MAIN_PROJECT_SOURCE_DIR}/install_dependencies.cmake.in ${CMAKE_BINARY_DIR}/install_dependencies.cmake @ONLY)
## Run the configured script at install time
#install(SCRIPT ${CMAKE_BINARY_DIR}/install_dependencies.cmake)

