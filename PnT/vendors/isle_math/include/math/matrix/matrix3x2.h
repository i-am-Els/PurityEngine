//
// Created by Eniola Olawale on 9/7/2024.
//

#pragma once

#include "vector2.h"
#include "vector3.h"
#include "core.h"
#include "matrix2x3.h"

namespace isle_engine::math
{
    template<typename T>
    class ISLE_API Matrix3x2
    {
    private:
        T m_data[3][2];
    public:
        Matrix3x2();
        explicit Matrix3x2(const T &value);
        explicit Matrix3x2(const T (&data)[6]);
        Matrix3x2(const T &r00, const T &r01, const T &r10, const T &r11, const T &r20, const T &r21);
        explicit Matrix3x2(const T (&data)[3][2]);
        Matrix3x2(const Matrix3x2<T> &matrix);
        Matrix3x2(const Vector2<T> &r1, const Vector2<T> &r2, const Vector2<T> &r3);
        explicit Matrix3x2(const Vector2<T> &vector);
        ~Matrix3x2();


        // Operator overloads----------------------------------------------
        T *operator[](int index);
        const T *operator[](int index) const;

        Matrix3x2<T> operator+(const Matrix3x2<T> &matrix) const;
        Matrix3x2<T> operator+(const T &value) const;
        Matrix3x2<T> &operator+=(const Matrix3x2<T> &matrix);
        Matrix3x2<T> &operator+=(const T &value);

        Matrix3x2<T> operator-(const Matrix3x2<T> &matrix) const;
        Matrix3x2<T> operator-(const T &value) const;
        Matrix3x2<T> &operator-=(const Matrix3x2<T> &matrix);
        Matrix3x2<T> &operator-=(const T &value);

        Matrix3x2<T> operator*(const T &value) const;
        Matrix3x2<T> &operator*=(const T &value);

        // Matrix Multiplication
        Vector3<T> operator*(const Vector2<T> &vector) const;
        Matrix3x2<T> operator*(const Matrix2<T> &matrix) const;
        Matrix3<T> operator*(const Matrix2x3<T> &matrix) const;
        Matrix3x4<T> operator*(const Matrix2x4<T> &matrix) const;

        Matrix3x2<T> operator/(const T &value) const;
        Matrix3x2<T> &operator/=(const T &value);

        Matrix2x3<T> transpose() const;
    };

    template<typename T>
    Matrix2x3 <T> Matrix3x2<T>::transpose() const {
        return Matrix2x3<T>(
                m_data[0][0],
                m_data[1][0],
                m_data[2][1],
                m_data[0][1],
                m_data[1][1],
                m_data[2][1]
        );
    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(): m_data{{}}
    {

    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(const T &value) : m_data{value, value, value, value, value, value}
    {
    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(const T (&data)[6]): m_data{data[0], data[1], data[2], data[3], data[4], data[5]}
    {
    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(const T &r00, const T &r01, const T &r10, const T &r11, const T &r20, const T &r21): m_data{r00, r01, r10, r11, r20, r21}
    {
    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(const T (&data)[3][2]): m_data{data[0][0], data[0][1], data[1][0], data[1][1], data[2][0], data[2][1]}
    {
    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(const Matrix3x2<T> &matrix): m_data{matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1], matrix[2][0], matrix[2][1]}
    {
    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(const Vector2<T> &r1, const Vector2<T> &r2, const Vector2<T> &r3): m_data{r1.x, r1.y, r2.x, r2.y, r3.x, r3.y}
    {
    }

    template<typename T>
    Matrix3x2<T>::Matrix3x2(const Vector2<T> &vector): m_data{vector.x, vector.y, vector.x, vector.y, vector.x, vector.y}
    {
    }

    template<typename T>
    Matrix3x2<T>::~Matrix3x2() = default;

    // Operator overloads----------------------------------------------
    template<typename T>
    T *Matrix3x2<T>::operator[](int index) {
        try{
            return m_data[index];
        }
        catch(...){
            std::cout << "Index out of Bounds!"<< std::endl;
        }
    }

    template<typename T>
    const T *Matrix3x2<T>::operator[](int index) const {
        try{
            return m_data[index];
        }
        catch(...){
            std::cout << "Index out of Bounds!"<< std::endl;
        }
    }

    template<typename T>
    Matrix3x2<T> Matrix3x2<T>::operator+(const Matrix3x2<T> &matrix) const {

        return Matrix3x2<T>(
                matrix[0][0] + (*this)[0][0],
                matrix[0][1] + (*this)[0][1],
                matrix[1][0] + (*this)[1][0],
                matrix[1][1] + (*this)[1][1],
                matrix[2][0] + (*this)[2][0],
                matrix[2][1] + (*this)[2][1]
        );
    }

    template<typename T>
    Matrix3x2<T> Matrix3x2<T>::operator+(const T &value) const {
        return Matrix3x2<T>(
                (*this)[0][0] + value,
                (*this)[0][1] + value,
                (*this)[1][0] + value,
                (*this)[1][1] + value,
                (*this)[2][0] + value,
                (*this)[2][1] + value
        );
    }

    template<typename T>
    Matrix3x2<T> &Matrix3x2<T>::operator+=(const Matrix3x2<T> &matrix) {
        (*this)[0][0] += matrix[0][0];
        (*this)[0][1] += matrix[0][1];
        (*this)[1][0] += matrix[1][0];
        (*this)[1][1] += matrix[1][1];
        (*this)[2][0] += matrix[2][0];
        (*this)[2][1] += matrix[2][1];
        return *this;
    }

    template<typename T>
    Matrix3x2<T> &Matrix3x2<T>::operator+=(const T &value) {
        (*this)[0][0] += value;
        (*this)[0][1] += value;
        (*this)[1][0] += value;
        (*this)[1][1] += value;
        (*this)[2][0] += value;
        (*this)[2][1] += value;
        return *this;
    }

    template<typename T>
    Matrix3x2<T> Matrix3x2<T>::operator-(const Matrix3x2<T> &matrix) const {
        return Matrix3x2<T>(
                (*this)[0][0] - matrix[0][0],
                (*this)[0][1] - matrix[0][1],
                (*this)[1][0] - matrix[1][0],
                (*this)[1][1] - matrix[1][1],
                (*this)[2][0] - matrix[2][0],
                (*this)[2][1] - matrix[2][1]
        );
    }

    template<typename T>
    Matrix3x2<T> Matrix3x2<T>::operator-(const T &value) const {
        return Matrix3x2<T>(
                (*this)[0][0] - value,
                (*this)[0][1] - value,
                (*this)[1][0] - value,
                (*this)[1][1] - value,
                (*this)[2][0] - value,
                (*this)[2][1] - value
        );
    }

    template<typename T>
    Matrix3x2<T> &Matrix3x2<T>::operator-=(const Matrix3x2<T> &matrix) {
        (*this)[0][0] -= matrix[0][0];
        (*this)[0][1] -= matrix[0][1];
        (*this)[1][0] -= matrix[1][0];
        (*this)[1][1] -= matrix[1][1];
        (*this)[2][0] -= matrix[2][0];
        (*this)[2][1] -= matrix[2][1];
        return *this;
    }

    template<typename T>
    Matrix3x2<T> &Matrix3x2<T>::operator-=(const T &value) {
        (*this)[0][0] -= value;
        (*this)[0][1] -= value;
        (*this)[1][0] -= value;
        (*this)[1][1] -= value;
        (*this)[2][0] -= value;
        (*this)[2][1] -= value;
        return *this;
    }

    template<typename T>
    Matrix3x2<T> Matrix3x2<T>::operator*(const T &value) const {
        return Matrix3x2<T>(
                (*this)[0][0] * value,
                (*this)[0][1] * value,
                (*this)[1][0] * value,
                (*this)[1][1] * value,
                (*this)[2][0] * value,
                (*this)[2][1] * value
        );
    }

    template<typename T>
    Matrix3x2<T> &Matrix3x2<T>::operator*=(const T &value) {
        (*this)[0][0] *= value;
        (*this)[0][1] *= value;
        (*this)[1][0] *= value;
        (*this)[1][1] *= value;
        (*this)[2][0] *= value;
        (*this)[2][1] *= value;
        return *this;
    }

    template<typename T>
    Vector3<T> Matrix3x2<T>::operator*(const Vector2<T> &vector) const {
        return Vector3<T>(
                ((*this)[0][0] * vector.x) + ((*this)[0][1] * vector.y),
                ((*this)[1][0] * vector.x) + ((*this)[1][1] * vector.y),
                ((*this)[2][0] * vector.x) + ((*this)[2][1] * vector.y)
        );
    }

    template<typename T>
    Matrix3x2<T> Matrix3x2<T>::operator*(const Matrix2<T> &matrix) const{
        return Matrix3x2<T>(
                ((*this)[0][0] * matrix[0][0]) + ((*this)[0][1] * matrix[1][0]),
                ((*this)[0][0] * matrix[0][1]) + ((*this)[0][1] * matrix[1][1]),
                ((*this)[1][0] * matrix[0][0]) + ((*this)[1][1] * matrix[1][0]),
                ((*this)[1][0] * matrix[0][1]) + ((*this)[1][1] * matrix[1][1]),
                ((*this)[2][0] * matrix[0][0]) + ((*this)[2][1] * matrix[1][0]),
                ((*this)[2][0] * matrix[0][1]) + ((*this)[2][1] * matrix[1][1])
        );
    }

    template<typename T>
    Matrix3<T> Matrix3x2<T>::operator*(const Matrix2x3<T> &matrix) const{
        return Matrix3<T>(
                ((*this)[0][0] * matrix[0][0]) + ((*this)[0][1] * matrix[1][0]),
                ((*this)[0][0] * matrix[0][1]) + ((*this)[0][1] * matrix[1][1]),
                ((*this)[0][0] * matrix[0][2]) + ((*this)[0][1] * matrix[1][2]),
                ((*this)[1][0] * matrix[0][0]) + ((*this)[1][1] * matrix[1][0]),
                ((*this)[1][0] * matrix[0][1]) + ((*this)[1][1] * matrix[1][1]),
                ((*this)[1][0] * matrix[0][2]) + ((*this)[1][1] * matrix[1][2]),
                ((*this)[2][0] * matrix[0][0]) + ((*this)[2][1] * matrix[1][0]),
                ((*this)[2][0] * matrix[0][1]) + ((*this)[2][1] * matrix[1][1]),
                ((*this)[2][0] * matrix[0][2]) + ((*this)[2][1] * matrix[1][2])
        );
    }

    template<typename T>
    Matrix3x4<T> Matrix3x2<T>::operator*(const Matrix2x4<T> &matrix) const {
        return Matrix3x4<T>(
                // First row
                ((*this)[0][0] * matrix[0][0]) + ((*this)[0][1] * matrix[1][0]),
                ((*this)[0][0] * matrix[0][1]) + ((*this)[0][1] * matrix[1][1]),
                ((*this)[0][0] * matrix[0][2]) + ((*this)[0][1] * matrix[1][2]),
                ((*this)[0][0] * matrix[0][3]) + ((*this)[0][1] * matrix[1][3]),

                // Second row
                ((*this)[1][0] * matrix[0][0]) + ((*this)[1][1] * matrix[1][0]),
                ((*this)[1][0] * matrix[0][1]) + ((*this)[1][1] * matrix[1][1]),
                ((*this)[1][0] * matrix[0][2]) + ((*this)[1][1] * matrix[1][2]),
                ((*this)[1][0] * matrix[0][3]) + ((*this)[1][1] * matrix[1][3]),

                // Third row
                ((*this)[2][0] * matrix[0][0]) + ((*this)[2][1] * matrix[1][0]),
                ((*this)[2][0] * matrix[0][1]) + ((*this)[2][1] * matrix[1][1]),
                ((*this)[2][0] * matrix[0][2]) + ((*this)[2][1] * matrix[1][2]),
                ((*this)[2][0] * matrix[0][3]) + ((*this)[2][1] * matrix[1][3])
        );
    }

    template<typename T>
    Matrix3x2<T> Matrix3x2<T>::operator/(const T &value) const {
        return Matrix3x2<T>(
                (*this)[0][0] / value,
                (*this)[0][1] / value,
                (*this)[1][0] / value,
                (*this)[1][1] / value,
                (*this)[2][0] / value,
                (*this)[2][1] / value
        );
    }

    template<typename T>
    Matrix3x2<T> &Matrix3x2<T>::operator/=(const T &value) {
        (*this)[0][0] /= value;
        (*this)[0][1] /= value;
        (*this)[1][0] /= value;
        (*this)[1][1] /= value;
        (*this)[2][0] /= value;
        (*this)[2][1] /= value;
        return *this;
    }
}

