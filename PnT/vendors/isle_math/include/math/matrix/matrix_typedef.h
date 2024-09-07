//
// Created by Eniola Olawale on 9/7/2024.
//

#pragma once

#include "matrix2.h"
#include "matrix2x3.h"
#include "matrix2x4.h"
#include "matrix3x2.h"
#include "matrix3.h"
#include "matrix3x4.h"
#include "matrix4x2.h"
#include "matrix4x3.h"
#include "matrix4.h"

namespace isle_engine::math{

    typedef Matrix2<short> Matrix2s;
    typedef Matrix2<int> Matrix2i;
    typedef Matrix2<float> Matrix2f;
    typedef Matrix2<double> Matrix2d;

    typedef Matrix2x3<short> Matrix2x3s;
    typedef Matrix2x3<int> Matrix2x3i;
    typedef Matrix2x3<float> Matrix2x3f;
    typedef Matrix2x3<double> Matrix2x3d;

    typedef Matrix2x4<short> Matrix2x4s;
    typedef Matrix2x4<int> Matrix2x4i;
    typedef Matrix2x4<float> Matrix2x4f;
    typedef Matrix2x4<double> Matrix2x4d;

    typedef Matrix3x2<short> Matrix3x2s;
    typedef Matrix3x2<int> Matrix3x2i;
    typedef Matrix3x2<float> Matrix3x2f;
    typedef Matrix3x2<double> Matrix3x2d;

    typedef Matrix3<short> Matrix3s;
    typedef Matrix3<int> Matrix3i;
    typedef Matrix3<float> Matrix3f;
    typedef Matrix3<double> Matrix3d;

    typedef Matrix3x4<short> Matrix3x4s;
    typedef Matrix3x4<int> Matrix3x4i;
    typedef Matrix3x4<float> Matrix3x4f;
    typedef Matrix3x4<double> Matrix3x4d;

    typedef Matrix4x2<short> Matrix4x2s;
    typedef Matrix4x2<int> Matrix4x2i;
    typedef Matrix4x2<float> Matrix4x2f;
    typedef Matrix4x2<double> Matrix4x2d;

    typedef Matrix4x3<short> Matrix4x3s;
    typedef Matrix4x3<int> Matrix4x3i;
    typedef Matrix4x3<float> Matrix4x3f;
    typedef Matrix4x3<double> Matrix4x3d;

    typedef Matrix4<short> Matrix4s;
    typedef Matrix4<int> Matrix4i;
    typedef Matrix4<float> Matrix4f;
    typedef Matrix4<double> Matrix4d;
}
