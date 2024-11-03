//
// Created by AWA on 30/10/2023.
//

#pragma once

#include "vector2.h"
#include "vector4.h"
#include "core.h"

namespace isle_engine::math
{
    template<typename T>
    class Matrix2x3;

    template<typename T>
    class Matrix2x4;

    template<typename T>
    class ISLE_API Matrix2
    {
    private:
        T m_data[2][2];
    public:
        Matrix2();
        explicit Matrix2(const T &value);
        explicit Matrix2(const T (&data)[4]);
        Matrix2(const T &r00, const T &r01, const T &r10, const T &r11);
        explicit Matrix2(const T (&data)[2][2]);
        Matrix2(const Matrix2<T> &matrix);
        Matrix2(const Vector2<T> &r1, const Vector2<T> &r2);
        explicit Matrix2(const Vector4<T> &vector);
        ~Matrix2();

        static Matrix2<T> identity();

        // Operator overloads----------------------------------------------
        T *operator[](int index);
        const T *operator[](int index) const;

        Matrix2<T> operator+(const Matrix2<T> &matrix) const;
        Matrix2<T> operator+(const T &value) const;
        Matrix2<T> &operator+=(const Matrix2<T> &matrix);
        Matrix2<T> &operator+=(const T &value);

        Matrix2<T> operator-(const Matrix2<T> &matrix) const;
        Matrix2<T> operator-(const T &value) const;
        Matrix2<T> &operator-=(const Matrix2<T> &matrix);
        Matrix2<T> &operator-=(const T &value);

        Matrix2<T> operator*(const T &value) const;
        Matrix2<T> &operator*=(const T &value);

        // Matrix Multiplication
        Vector2<T> operator*(const Vector2<T> &vector) const;
        Matrix2<T> operator*(const Matrix2<T> &matrix) const;
        Matrix2x3<T> operator*(const Matrix2x3<T> &matrix) const;
        Matrix2x4<T> operator*(const Matrix2x4<T> &matrix) const;

        Matrix2<T> operator/(const T &value) const;
        Matrix2<T> &operator/=(const T &value);

        Matrix2<T> transpose() const;
    };

    template<typename T>
    Matrix2<T> Matrix2<T>::identity() {
        return Matrix2<T>(1.0f, 0.0f,
                          0.0f, 1.0f);
    }


    template<typename T>
    Matrix2<T> Matrix2<T>::transpose() const {
        return Matrix2<T>(
                m_data[0][0],
                m_data[1][0],
                m_data[0][1],
                m_data[1][1]
                );
    }

    template<typename T>
    Matrix2<T>::Matrix2(): m_data{{}}
    {
    }

    template<typename T>
    Matrix2<T>::Matrix2(const T &value) : m_data{value, value, value, value}
    {
    }

    template<typename T>
    Matrix2<T>::Matrix2(const T (&data)[4]): m_data{data[0], data[1], data[2], data[3]}
    {
    }

    template<typename T>
    Matrix2<T>::Matrix2(const T &r00, const T &r01, const T &r10, const T &r11): m_data{r00, r01, r10, r11}
    {
    }

    template<typename T>
    Matrix2<T>::Matrix2(const T (&data)[2][2]): m_data{data[0][0], data[0][1], data[1][0], data[1][1]}
    {
    }

    template<typename T>
    Matrix2<T>::Matrix2(const Matrix2<T> &matrix): m_data{matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]}
    {
    }

    template<typename T>
    Matrix2<T>::Matrix2(const Vector2<T> &r1, const Vector2<T> &r2): m_data{r1.x, r1.y, r2.x, r2.y}
    {
    }

    template<typename T>
    Matrix2<T>::Matrix2(const Vector4<T> &vector): m_data{vector.x, vector.y, vector.z, vector.w}
    {
    }

    template<typename T>
    Matrix2<T>::~Matrix2() = default;

    // Operator overloads----------------------------------------------
    template<typename T>
    T *Matrix2<T>::operator[](int index) {
        try{
            return m_data[index];
        }
        catch(...){
            std::cout << "Index out of Bounds!"<< std::endl;
        }
    }

    template<typename T>
    const T *Matrix2<T>::operator[](int index) const {
        try{
            return m_data[index];
        }
        catch(...){
            std::cout << "Index out of Bounds!"<< std::endl;
        }
    }

    template<typename T>
    Matrix2<T> Matrix2<T>::operator+(const Matrix2<T> &matrix) const {

        return Matrix2<T>(
            matrix[0][0] + (*this)[0][0],
            matrix[0][1] + (*this)[0][1],
            matrix[1][0] + (*this)[1][0],
            matrix[1][1] + (*this)[1][1]
        );
    }

    template<typename T>
    Matrix2<T> Matrix2<T>::operator+(const T &value) const {
        return Matrix2<T>(
            (*this)[0][0] + value,
            (*this)[0][1] + value,
            (*this)[1][0] + value,
            (*this)[1][1] + value
        );
    }

    template<typename T>
    Matrix2<T> &Matrix2<T>::operator+=(const Matrix2<T> &matrix) {
        (*this)[0][0] += matrix[0][0];
        (*this)[0][1] += matrix[0][1];
        (*this)[1][0] += matrix[1][0];
        (*this)[1][1] += matrix[1][1];
        return *this;
    }

    template<typename T>
    Matrix2<T> &Matrix2<T>::operator+=(const T &value) {
        (*this)[0][0] += value;
        (*this)[0][1] += value;
        (*this)[1][0] += value;
        (*this)[1][1] += value;
        return *this;
    }

    template<typename T>
    Matrix2<T> Matrix2<T>::operator-(const Matrix2<T> &matrix) const {
        return Matrix2<T>(
            (*this)[0][0] - matrix[0][0],
            (*this)[0][1] - matrix[0][1],
            (*this)[1][0] - matrix[1][0],
            (*this)[1][1] - matrix[1][1]
        );
    }

    template<typename T>
    Matrix2<T> Matrix2<T>::operator-(const T &value) const {
        return Matrix2<T>(
            (*this)[0][0] - value,
            (*this)[0][1] - value,
            (*this)[1][0] - value,
            (*this)[1][1] - value
        );
    }

    template<typename T>
    Matrix2<T> &Matrix2<T>::operator-=(const Matrix2<T> &matrix) {
        (*this)[0][0] -= matrix[0][0];
        (*this)[0][1] -= matrix[0][1];
        (*this)[1][0] -= matrix[1][0];
        (*this)[1][1] -= matrix[1][1];
        return *this;
    }

    template<typename T>
    Matrix2<T> &Matrix2<T>::operator-=(const T &value) {
        (*this)[0][0] -= value;
        (*this)[0][1] -= value;
        (*this)[1][0] -= value;
        (*this)[1][1] -= value;
        return *this;
    }

    template<typename T>
    Matrix2<T> Matrix2<T>::operator*(const T &value) const {
        return Matrix2<T>(
            (*this)[0][0] * value,
            (*this)[0][1] * value,
            (*this)[1][0] * value,
            (*this)[1][1] * value
        );
    }

    template<typename T>
    Matrix2<T> &Matrix2<T>::operator*=(const T &value) {
        (*this)[0][0] *= value;
        (*this)[0][1] *= value;
        (*this)[1][0] *= value;
        (*this)[1][1] *= value;
        return *this;
    }

    template<typename T>
    Vector2<T> Matrix2<T>::operator*(const Vector2<T> &vector) const {
        return Vector2<T>(
            (*this)[0][0] * vector.x + (*this)[0][1] * vector.y,
            (*this)[1][0] * vector.x + (*this)[1][1] * vector.y
        );
    }

    template<typename T>
    Matrix2<T> Matrix2<T>::operator*(const Matrix2<T> &matrix) const {
        return Matrix2<T>(
                (*this)[0][0] * matrix[0][0] + (*this)[0][1] * matrix[1][0],
                (*this)[0][0] * matrix[0][1] + (*this)[0][1] * matrix[1][1],
                (*this)[1][0] * matrix[0][0] + (*this)[1][1] * matrix[1][0],
                (*this)[1][0] * matrix[0][1] + (*this)[1][1] * matrix[1][1]
        );
    }

    template<typename T>
    Matrix2x3<T> Matrix2<T>::operator*(const Matrix2x3<T> &matrix) const {
        return Matrix2x3<T>(
                ((*this)[0][0] * matrix[0][0]) + ((*this)[0][1] * matrix[1][0]),
                ((*this)[0][0] * matrix[0][1]) + ((*this)[0][1] * matrix[1][1]),
                ((*this)[0][0] * matrix[0][2]) + ((*this)[0][1] * matrix[1][2]),
                ((*this)[1][0] * matrix[0][0]) + ((*this)[1][1] * matrix[1][0]),
                ((*this)[1][0] * matrix[0][1]) + ((*this)[1][1] * matrix[1][1]),
                ((*this)[1][0] * matrix[0][2]) + ((*this)[1][1] * matrix[1][2])
        );
    }

    template<typename T>
    Matrix2x4<T> Matrix2<T>::operator*(const Matrix2x4<T> &matrix) const {
        return Matrix2x4<T>(
                ((*this)[0][0] * matrix[0][0]) + ((*this)[0][1] * matrix[1][0]),
                ((*this)[0][0] * matrix[0][1]) + ((*this)[0][1] * matrix[1][1]),
                ((*this)[0][0] * matrix[0][2]) + ((*this)[0][1] * matrix[1][2]),
                ((*this)[0][0] * matrix[0][3]) + ((*this)[0][1] * matrix[1][3]),
                ((*this)[1][0] * matrix[0][0]) + ((*this)[1][1] * matrix[1][0]),
                ((*this)[1][0] * matrix[0][1]) + ((*this)[1][1] * matrix[1][1]),
                ((*this)[1][0] * matrix[0][2]) + ((*this)[1][1] * matrix[1][2]),
                ((*this)[1][0] * matrix[0][3]) + ((*this)[1][1] * matrix[1][3])
                );
    }

    template<typename T>
    Matrix2<T> Matrix2<T>::operator/(const T &value) const {
        return Matrix2<T>(
            (*this)[0][0] / value,
            (*this)[0][1] / value,
            (*this)[1][0] / value,
            (*this)[1][1] / value
        );
    }

    template<typename T>
    Matrix2<T> &Matrix2<T>::operator/=(const T &value) {
        (*this)[0][0] /= value;
        (*this)[0][1] /= value;
        (*this)[1][0] /= value;
        (*this)[1][1] /= value;
        return *this;
    }
}
