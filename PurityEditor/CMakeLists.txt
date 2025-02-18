# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.


# Minimum required version of CMake
cmake_minimum_required(VERSION 3.26)

project(PurityEngine:PurityEditor VERSION 0.1.2 LANGUAGES CXX)
#project(PurityEngine VERSION 0.1.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

include(GNUInstallDirs)

find_package(cereal CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(nlohmann_json_schema_validator CONFIG REQUIRED)

add_executable(PurityEditor
        gui/src/editor.cpp
        gui/include/editor.h
        gui/src/p_editor_application.cpp
        gui/include/p_editor_application.h
)


# Add the core directory for the Purity library
target_include_directories(PurityEditor PRIVATE
#        ${CMAKE_SOURCE_DIR}/Purity/core
        gui/include
#        $<BUILD_INTERFACE:${Purity_INCLUDE_DIRS}>
#        $<BUILD_INTERFACE:${Purity_INCLUDE_DIRS}/core>
)

add_dependencies(PurityEditor IsleMath Purity)

# Link against the Purity library (assuming it's built in a sibling directory)
target_link_libraries(PurityEditor PRIVATE Purity cereal::cereal imgui::imgui glfw glad::glad ImGuiFileDialog nlohmann_json::nlohmann_json nlohmann_json_schema_validator::validator)

target_compile_definitions(PurityEditor PUBLIC PURITY_PLATFORM_WINDOWS)

# Specify the installation directory for the Game executable
install(TARGETS PurityEditor DESTINATION ${CMAKE_INSTALL_BINDIR})

add_custom_command(TARGET PurityEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t "${CMAKE_INSTALL_PREFIX}/bin" $<TARGET_RUNTIME_DLLS:PurityEditor>
        COMMAND_EXPAND_LISTS
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

