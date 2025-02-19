cmake_minimum_required(VERSION 3.26)

project(PurityEngine:Commons VERSION 0.1.2 LANGUAGES CXX)
#project(PurityEngine VERSION 0.1.2 LANGUAGES CXX)

set(BUILD_SHARED_LIBS ON)

option(Commons_INSTALL "Install Commons library" ON)
option(Commons_EXPORT "Export Commons targets for downstream projects" ON)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(nlohmann_json_schema_validator CONFIG REQUIRED)

add_library(Commons SHARED 
		include/serialize_utilities.h
		src/serialize_utilities.cpp
        include/uuid.h
        src/uuid.cpp
        include/common_macros.h
)

target_link_libraries(Commons PRIVATE nlohmann_json::nlohmann_json nlohmann_json_schema_validator::validator)

target_compile_definitions(
        Commons
        PUBLIC
        PURITY_PLATFORM_WINDOWS
        COMMON_BUILD_DLL
)

include(GNUInstallDirs)

target_include_directories(
        Commons
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Commons>
)

if(Commons_INSTALL)

    install(DIRECTORY include/             DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Commons)
    # Install the Commons library and headers
    install(TARGETS Commons
            EXPORT CommonsTargets
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(EXPORT CommonsTargets
            FILE CommonsTargets.cmake
            NAMESPACE Commons::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Commons)

    include(CMakePackageConfigHelpers)

    # Configure the main CommonsConfig.cmake file from a template
    configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/CommonsConfig.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/CommonsConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Commons)

    # Write version file for the package
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/CommonsConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
    )


    # Install the config files
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/CommonsConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/CommonsConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Commons
    )
endif ()

if (Commons_EXPORT)
    export(EXPORT CommonsTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/CommonsTargets.cmake"
            NAMESPACE Commons::
    )
endif ()