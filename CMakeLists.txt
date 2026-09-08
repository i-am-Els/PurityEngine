# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

# Define the project name
project(PurityEngine VERSION 0.1.2  LANGUAGES CXX)

# Set the C++ standard (adjust as needed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Optional safeguard for MSVC
if(MSVC)
    add_compile_options(/Zc:__cplusplus /std:c++20)
endif()

set(USING_PACKAGE_MANAGER_VCPKG ON CACHE BOOL "Use the package manager")

include(GNUInstallDirs)

# Check for MSVC compiler
if(MSVC)
    message(STATUS "Using Microsoft Visual Studio Compiler")
    # Set specific flags for MSVC
    add_compile_options(/W4)  # Set warning level to 4
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Using GCC Compiler")
    # Set specific flags for GCC
    add_compile_options(-Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang Compiler")
    # Set specific flags for Clang
    add_compile_options(-Wall -Wextra)
endif()

# --- Put this BEFORE add_subdirectory ---
# 1. Fixes Visual Studio & VS Code CMake Tools debugging
set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# 2. Fixes modern IDE launchers (CMake 3.31+)
if(POLICY CMP0178) # Ensures compatibility flags if active
    cmake_policy(SET CMP0178 NEW)
endif()
set(CMAKE_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Ensure the directories exist before installation
file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")
file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib")
file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/include")


add_subdirectory(vendors/isle_math)
add_subdirectory(vendors/ImGuiFileDialog)
add_subdirectory(Commons)
add_subdirectory(Purity)
add_subdirectory(PurityEditor)
add_subdirectory(PurityGem)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")