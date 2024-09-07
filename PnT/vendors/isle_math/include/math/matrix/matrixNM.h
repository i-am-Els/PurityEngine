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


    template<int N, int M, typename T>
    MatrixNM<N, M, T>::MatrixNM(): m_data{{}}
    {

    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T>::MatrixNM(const T &value)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                *((*(m_data + i)) + j) = value;
            }
        }
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T>::MatrixNM(const T (&data)[N * M])
    {

        for (int i = 0; i < m_size; i++)
        {
            *((*(m_data + i / 2)) + i % 2) = *(data + i);
        }
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T>::MatrixNM(const T (&data)[N][M])
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                *((*(m_data + i)) + j) = *(*(data + i) + j);
            }
        }
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T>::MatrixNM(const MatrixNM<N, M, T> &matrix): MatrixNM(matrix.m_data)
    {

    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T>::~MatrixNM() = default;

    template<int N, int M, typename T>
    int MatrixNM<N, M, T>::size() const
    {
        return m_size;
    }

    template<int N, int M, typename T>
    int MatrixNM<N, M, T>::rowsize() const
    {
        return N;
    }

    template<int N, int M, typename T>
    int MatrixNM<N, M, T>::columnsize() const
    {
        return M;
    }


    template<int N, int M, typename T>
    T MatrixNM<N, M, T>::get(int i, int j) const
    {
        return *((*(m_data + i)) + j);
    }

    template<int N, int M, typename T>
    void MatrixNM<N, M, T>::set(int i, int j, T value)
    {
        *((*(m_data + i)) + j) = value;
    }

    template<int N, int M, typename T>
    T MatrixNM<N, M, T>::sum() const
    {
        T matrix_sum = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                matrix_sum += this->m_data[i][j];
            }
        }
        return matrix_sum;
    }

    // ----------------------------------- Accessor ---------------------------------
    template<int N, int M, typename T>
    T *MatrixNM<N, M, T>::operator[](int index)
    {
        return m_data[index];
    }

    template<int N, int M, typename T>
    const T *MatrixNM<N, M, T>::operator[](int index) const
    {
        return m_data[index];
    }

    /*
    template<int N, int M, typename T>
    T &MatrixNM<N, M, T>::operator()(int row, int col)
    {
        return m_data[row][col];
    }

    template<int N, int M, typename T>
    const T &MatrixNM<N, M, T>::operator()(int row, int col) const
    {
        return m_data[row][col];
    }
    */

    // ----------------------------------- Addition ---------------------------------
    template<int N, int M, typename T>
    MatrixNM<N, M, T> MatrixNM<N, M, T>::operator+(const MatrixNM<N, M, T> &matrix) const
    {
        MatrixNM<N, M, T> result;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_data[i][j] = this->m_data[i][j] + matrix.m_data[i][j];
            }
        }
        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> MatrixNM<N, M, T>::operator+(const T &value) const
    {
        MatrixNM<N, M, T> result;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_data[i][j] = this->m_data[i][j] + value;
            }
        }

        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> &MatrixNM<N, M, T>::operator+=(const MatrixNM<N, M, T> &matrix)
    {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->m_data[i][j] = this->m_data[i][j] + matrix.m_data[i][j];
            }
        }

        return *this;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> &MatrixNM<N, M, T>::operator+=(const T &value)
    {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->m_data[i][j] = this->m_data[i][j] + value;
            }
        }

        return *this;
    }

    // ----------------------------------- Subtraction -------------------------------
    template<int N, int M, typename T>
    MatrixNM<N, M, T> MatrixNM<N, M, T>::operator-(const MatrixNM<N, M, T> &matrix) const
    {
        MatrixNM<N, M, T> result;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_data[i][j] = this->m_data[i][j] - matrix.m_data[i][j];
            }
        }
        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> MatrixNM<N, M, T>::operator-(const T &value) const
    {
        MatrixNM<N, M, T> result;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_data[i][j] = this->m_data[i][j] - value;
            }
        }

        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> &MatrixNM<N, M, T>::operator-=(const MatrixNM<N, M, T> &matrix)
    {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->m_data[i][j] = this->m_data[i][j] - matrix.m_data[i][j];
            }
        }

        return *this;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> &MatrixNM<N, M, T>::operator-=(const T &value)
    {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->m_data[i][j] = this->m_data[i][j] - value;
            }
        }

        return *this;
    }

    // -------------------------------- Multiplication -----------------------------
    template<int N, int M, typename T>
    template<int N1, int M1>
    MatrixNM<N, M1, T> MatrixNM<N, M, T>::operator*(const MatrixNM<N1, M1, T> &matrix) const
    {

        static_assert(M == N1, "Other matrix must have the same number of columns as this row size");

        MatrixNM<N, M1, T> result;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M1; j++)
            {
                T mul = 0;
                for (int k = 0; k < N1; k++)
                {
                    mul += this->m_data[i][k] * matrix[k][j];
                }
                result[i][j] = mul;
            }
        }

        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> MatrixNM<N, M, T>::operator*(const T &value) const
    {
        MatrixNM<N, M, T> result;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_data[i][j] = this->m_data[i][j] * value;
            }
        }

        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> &MatrixNM<N, M, T>::operator*=(const T &value)
    {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->m_data[i][j] = this->m_data[i][j] * value;
            }
        }

        return *this;
    }


    // -------------------------------- Division -----------------------------
    template<int N, int M, typename T>
    MatrixNM<N, M, T> MatrixNM<N, M, T>::operator/(const T &value) const
    {
        MatrixNM<N, M, T> result;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_data[i][j] = this->m_data[i][j] / value;
            }
        }

        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> &MatrixNM<N, M, T>::operator/=(const T &value)
    {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->m_data[i][j] = this->m_data[i][j] / value;
            }
        }

        return *this;
    }

    // -------------------------------- Modulus -----------------------------
    template<int N, int M, typename T>
    MatrixNM<N, M, T> MatrixNM<N, M, T>::operator%(const T &value) const
    {
        MatrixNM<N, M, T> result;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_data[i][j] = this->m_data[i][j] % value;
            }
        }

        return result;
    }

    template<int N, int M, typename T>
    MatrixNM<N, M, T> &MatrixNM<N, M, T>::operator%=(const T &value)
    {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                this->m_data[i][j] = this->m_data[i][j] % value;
            }
        }

        return *this;
    }

    // --------------------------- Matrix Transpose -----------------------
    template<int N, int M, typename T>
    MatrixNM<M, N, T> MatrixNM<N, M, T>::transpose() const {

        MatrixNM<M, N, T> transposed;

        for (int j = 0; j < M; j++) {
            for (int i = 0; i < N; i++) {
                transposed[j][i] = this->m_data[i][j];
            }
        }

        return transposed;
    }

    // --------------------------- Matrix Determinant -----------------------



    //Extras-----------------------
    template<int N, int M, typename T>
    T &operator+=(T &value_left, const MatrixNM<N, M, T> &matrix_right)
    {
        value_left += matrix_right.sum();
        return value_left;
    }

    template<int N, int M, typename T>
    std::ostream &operator<<(std::ostream& out, const MatrixNM<N, M, T> &matrix)
    {
        out << "Matrix(\n";

        size_t max = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                T element = matrix.get(i, j);

                std::string e = std::to_string(element);
                size_t l = e.length();

                if ( l > max)
                    max = l;
            }
        }

        for (int i = 0; i < N; i++)
        {
            int last_column = M - 1;
            out << "    |";
            for (int j = 0; j < last_column; j++)
            {
                out << justify_right(std::to_string(matrix.get(i, j)), max) << "    ";
            }
            out << justify_right(std::to_string(matrix.get(i, last_column)), max) << "|\n";
        }

        out << ")";
        return out;
    }
}


//#include "matrixNM.tpp"
