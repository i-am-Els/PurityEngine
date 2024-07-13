#pragma once
#include "core.h"
#include "vector3.h"


namespace isle_engine::math
{
    template <int N, int M, typename T>
    class ISLE_API MatrixNM
    {
    private:
        T m_data[N][M];
        int m_size = N * M;

    public:
        MatrixNM();
        MatrixNM(const T &value);
        MatrixNM(const T (&data)[N * M]);
        MatrixNM(const T (&data)[N][M]);
        MatrixNM(const MatrixNM<N, M, T> &matrix);
        ~MatrixNM();

        [[nodiscard]] int size() const;
        [[nodiscard]] int rowsize() const;
        [[nodiscard]] int columnsize() const;
        T get(int i, int j) const;
        void set(int i, int j, T value);
        T sum()const;

        // Operator overloads----------------------------------------------
        T *operator[](int index);
        const T *operator[](int index) const;
        // T& operator()(int i, int j);
        // const T& operator()(int i, int j) const;

        MatrixNM<N, M, T> operator+(const MatrixNM<N, M, T> &matrix) const;
        MatrixNM<N, M, T> operator+(const T &value) const;
        MatrixNM<N, M, T> &operator+=(const MatrixNM<N, M, T> &matrix);
        MatrixNM<N, M, T> &operator+=(const T &value);

        MatrixNM<N, M, T> operator-(const MatrixNM<N, M, T> &matrix) const;
        MatrixNM<N, M, T> operator-(const T &value) const;
        MatrixNM<N, M, T> &operator-=(const MatrixNM<N, M, T> &matrix);
        MatrixNM<N, M, T> &operator-=(const T &value);

        template<int N1, int M1>
        MatrixNM<N, M1, T> operator*(const MatrixNM<N1, M1, T> &matrix) const;
        MatrixNM<N, M, T> operator*(const T &value) const;
        MatrixNM<N, M, T> &operator*=(const T &value);

        MatrixNM<N, M, T> operator/(const T &value) const;
        MatrixNM<N, M, T> &operator/=(const T &value);

        MatrixNM<N, M, T> operator%(const T &value) const;
        MatrixNM<N, M, T> &operator%=(const T &value);

        MatrixNM<M, N, T> transpose() const;
//        T determinant() const;
//        MatrixNM<N, M, T> inverse() const;
//        MatrixNM<N, M, T> minor() const;
//        MatrixNM<N, M, T> decompose_lower();
//        MatrixNM<N, M, T> decompose_upper();

        // Elementary operations
//        MatrixNM<N, M, T> &row_interchange(int i, int j);
//        MatrixNM<N, M, T> &col_interchange(int i, int j);
//        MatrixNM<N, M, T> &row_scale(int i, T scale_value);
//        MatrixNM<N, M, T> &col_scale(int i, T scale_value);
//        MatrixNM<N, M, T> &row_combination(int i, int j, T scale_value);
//        MatrixNM<N, M, T> &col_combination(int i, int j, T scale_value);
    };

    template<int N, int M, typename T>
    std::ostream &operator<<(std::ostream& out, const MatrixNM<N, M, T>& matrix);

    template<int N, int M, typename T>
    T &operator+=(T & value_left, const MatrixNM<N, M, T>& matrix_right);


    typedef MatrixNM<2, 2, short> Matrix2s;
    typedef MatrixNM<2, 2, int> Matrix2i;
    typedef MatrixNM<2, 2, float> Matrix2f;
    typedef MatrixNM<2, 2, double> Matrix2d;

    typedef MatrixNM<3, 3, short> Matrix3s;
    typedef MatrixNM<3, 3, int> Matrix3i;
    typedef MatrixNM<3, 3, float> Matrix3f;
    typedef MatrixNM<3, 3, double> Matrix3d;

    typedef MatrixNM<3, 4, short> Matrix34s;
    typedef MatrixNM<3, 4, int> Matrix34i;
    typedef MatrixNM<3, 4, float> Matrix34f;
    typedef MatrixNM<3, 4, double> Matrix34d;

    typedef MatrixNM<4, 4, short> Matrix4s;
    typedef MatrixNM<4, 4, int> Matrix4i;
    typedef MatrixNM<4, 4, float> Matrix4f;
    typedef MatrixNM<4, 4, double> Matrix4d;

}


#include "matrixNM.tpp"
