# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.26)
project(Police_n_Thief)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES
        "src/*.cpp"
)

# Build the math src to static library (library name = "islemath")
add_library(
        islemath
        SHARED
        include/isle_pch.h
        ${SOURCE_FILES}
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
        include/math/islemath.h
        include/array_util.h
        include/core.h
        include/string_util.h
        src/isle_pch.cpp
        src/basis.cpp
        src/fraction.cpp
        src/transform.cpp
)

target_compile_definitions(
        islemath
        PUBLIC
        ISLE_PLATFORM_WINDOWS
        ISLE_BUILD_DLL
)

target_include_directories(
        islemath
        PUBLIC
        include
        include/math
        include/math/matrix
        include/math/vector
)

target_precompile_headers(islemath PRIVATE include/isle_pch.h)
