//
// Created by Eniola Olawale on 9/28/2023.
//

#pragma once
#include "matrixNM.h"
#include "vector3.h"
#include "quaternion.h"


namespace isle_engine::math
{

    template<class T>
    int largest(size_t len, T* argv){
        // Returns index of largest in argv
        size_t large = 0;
        size_t i = 0;
        size_t j = 1;
        while (i < (len - 1)){
            while ( j < len){
                if (argv[j] > argv[large]){
                    large = j;
                    i = j - 1;
                    j += 1;
                    break;
                }
                j++;
            }
            i++;
        }
        return (int)large;
    }


    // Conversions
    // .................................................................................................

    template<class T>
    Vector3<T> MatrixToEuler(const MatrixNM<3, 3, T>& m )
    {
        // Object to Upright
        // To convert Upright to Object, simply transposing the matrix before the function starts should do the trick
        // and **probably** switching the sign of the m[2][0], m[2][1], and m[0][1] afterwards
        T yaw, pitch, roll;
        T cell = -m[2][1];
        if (cell <= -1.0f)
            pitch = -0.5f * PI<T>;
        else if (cell >= 1.0f)
            pitch = 0.5f * PI<T>;
        else
            pitch = std::asin(cell);

        if (std::abs(cell) > T(1) - Epsilon<T>)
        {
            roll = T(0);
            yaw = std::atan2(-m[0][3], m[0][0]);
        }
        else
        {
            yaw = std::atan2(m[2][0], m[2][2]);
            roll = std::atan2(m[0][1], m[1][1]);
        }

        return Vector3<T>(pitch, yaw, roll);
    }

    template<class T>
    MatrixNM<3, 3, T> EulerToMatrix(T yaw, T pitch, T roll)
    {
        T cy, cp, cr, sy, sp, sr;
        cy = std::cos(yaw), sy = std::sin(yaw);
        cp = std::cos(pitch), sp = std::sin(pitch);
        cr = std::cos(roll), sr = std::sin(roll);

        // Object-to-Upright
        // To get Upright-to-Object, simply transposing the returned matrix should solve the case!.
        return MatrixNM<3, 3, T>(
                {
                        {(cy * cr) + (sy * sp * sr),      (sr * cp), (-1 * sy * sr) + (cy * sp * sr)},
                        {(-1 * cy * sr) + (sy * sp * cr), (cr * cp), (sr * sy) + (cy * sp * cr)},
                        {(sy * cp),                       (-1 * sp), (cy * cp)}
                }
                );
    }

    template<class T>
    Quaternion<T> EulerToQuaternion(T yaw, T pitch, T roll) {
        T cy, cp, cr, sy, sp, sr;
        cy = std::cos(yaw / 2), sy = std::sin(yaw / 2);
        cp = std::cos(pitch / 2), sp = std::sin(pitch / 2);
        cr = std::cos(roll / 2), sr = std::sin(roll / 2);
        // Object to  Upright
        // To find Upright to Object, simply find the conjugate of the resulting Quaternion
        return Quaternion<T>(
                (cy * cp * cr) + (sy * sp * sr),
                (cy * sp * cr) + (sy * cp * sr),
                (sy * cp * cr) - (cy * sp * sr),
                (cy * cp * sr) - (sy * sp * cr)
                );
    }

    template<class T>
    Vector3<T> QuaternionToEuler(Quaternion<T> q){
        //  Object to Upright
        // NOT COMPLETED
        return Vector3<T>();
    }

    template<class T>
    Quaternion<T> MatrixToQuaternion(const MatrixNM<3, 3, T>& m) {
        T w, x, y, z;
        // Find 4w^2 - 1, 4x^2 - 1, 4y^2 - 1, and 4z^2 - 1
        T fourW2diff1 = m[0][0] + m[1][1] + m[2][2];
        T fourX2diff1 = m[0][0] - m[1][1] - m[2][2];
        T fourY2diff1 = m[1][1] - m[0][0] - m[2][2];
        T fourZ2diff1 = m[2][2] - m[0][0] - m[1][1];

        T arr[4] = {fourW2diff1, fourX2diff1, fourY2diff1, fourZ2diff1};
        int index;
        // Find the largest of all, return an index of that
        index = largest(4, arr);

        T largestV = sqrt(arr[index] + T(1)) * 0.5f;
        T factor = 0.25f / largestV;

        switch (index) {
            case 0:
                w = largestV;
                x = (m[1][2] - m[2][1]) * factor;
                y = (m[2][0] - m[0][2]) * factor;
                z = (m[0][1] - m[1][0]) * factor;
                break;
            case 1:
                x = largestV;
                w = (m[1][2] - m[2][1]) * factor;
                y = (m[0][1] + m[1][0]) * factor;
                z = (m[2][0] + m[0][2]) * factor;
                break;
            case 2:
                y = largestV;
                w = (m[1][2] - m[2][1]) * factor;
                x = (m[0][1] + m[1][0]) * factor;
                z = (m[1][2] + m[2][1]) * factor;
                break;
            case 3:
                z = largestV;
                w = (m[0][1] - m[1][0]) * factor;
                x = (m[2][0] + m[0][2]) * factor;
                y = (m[1][2] + m[2][1]) * factor;
                break;
        }
        return Quaternion<T>(w, x, y, z);
    }

    template<class T>
    MatrixNM<3, 3, T> QuaternionToMatrix(Quaternion<T> q){
        return MatrixNM<3, 3, T>(
                {
                    {1 - (2 * (q.y * q.y)) - (2 * (q.z * q.z)), ((2 * q.x * q.y) + (2 * q.w * q.z)), ((2 * q.x * q.z) - (2 * q.w * q.y))},
                    {((2 * q.x * q.y) - (2 * q.w * q.z)), 1 - (2 * (q.x * q.x)) - (2 * (q.z * q.z)), ((2 * q.y * q.z) - (2 * q.w * q.x))},
                    {((2 * q.x * q.z) + (2 * q.w * q.y)), ((2 * q.y * q.z) - (2 * q.w * q.x)), 1 - (2 * (q.x * q.x)) - (2 * (q.y * q.y))}
                }
                );
    }

    // End of Conversions
    // .................................................................................................

}