# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.

cmake_minimum_required(VERSION 3.26)

project(Police_n_Thief VERSION 0.1.2)

option(IsleMath_INSTALL "Install IsleMath library" ON)
option(IsleMath_EXPORT "Export IsleMath targets for downstream projects" ON)

set(CMAKE_CXX_STANDARD 17)

# Build the math src to static library (library name = "IsleMath")
add_library(
        IsleMath
        SHARED
        include/isle_pch.h
        include/math/math_utils.h
        include/math/matrix/matrix2.h
        include/math/matrix/matrix3.h
        include/math/matrix/matrix4.h
        include/math/matrix/matrix4x3.h
        include/math/matrix/matrix3x4.h
        include/math/matrix/imatrix.h
        include/math/vector/vector2.h
        include/math/vector/vector3.h
        include/math/vector/vector4.h
        include/math/global.h
        include/math/conversions.h
        include/math/basis.h
        include/math/fraction.h
        include/math/quaternion.h
        include/math/transform.h
        include/math/isleMath.h
        include/array_util.h
        include/core.h
        include/string_util.h
        src/isle_pch.cpp
        src/math/basis.cpp
        src/math/fraction.cpp
        src/math/transform.cpp
        include/math/matrix/matrix2x3.h
        include/math/matrix/matrix3x2.h
        include/math/matrix/matrix2x4.h
        include/math/matrix/matrix4x2.h
        include/math/matrix/matrix_typedef.h
)

target_compile_definitions(
        IsleMath
        PUBLIC
        ISLE_PLATFORM_WINDOWS
        ISLE_BUILD_DLL
)

include(GNUInstallDirs)

target_include_directories(
        IsleMath
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/IsleMath>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/math>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/IsleMath/math>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/math/matrix>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/IsleMath/math/matrix>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/math/vector>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/IsleMath/math/vector>
)

target_precompile_headers(IsleMath PRIVATE include/isle_pch.h)


if(IsleMath_INSTALL)

    install(DIRECTORY include/             DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/IsleMath)
    install(DIRECTORY include/math/        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/IsleMath/math)
    install(DIRECTORY include/math/matrix/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/IsleMath/math/matrix)
    install(DIRECTORY include/math/vector/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/IsleMath/math/vector)


    # Install the IsleMath library and headers
    install(TARGETS IsleMath
            EXPORT IsleMathTargets
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(EXPORT IsleMathTargets
            FILE IsleMathTargets.cmake
            NAMESPACE IsleMath::
            DESTINATION lib/cmake/IsleMath)

    include(CMakePackageConfigHelpers)

    # Configure the main IsleMathConfig.cmake file from a template
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/IsleMathConfig.cmake.in
            ${CMAKE_CURRENT_BINARY_DIR}/IsleMathConfig.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/IsleMath)

    # Write version file for the package
    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/IsleMathConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion
    )


    # Install the config files
    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/IsleMathConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/IsleMathConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/IsleMath
    )
endif ()

if (IsleMath_EXPORT)
    export(EXPORT IsleMathTargets
            FILE "${CMAKE_CURRENT_BINARY_DIR}/IsleMathTargets.cmake"
            NAMESPACE IsleMath::
    )
endif ()