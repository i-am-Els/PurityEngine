#pragma once
#include "core.h"
#include "global.h"

    namespace isle_engine::math
    {
        /**
         * @brief Represents a 2D vector.
         *
         * This class represents a 2D vector with x and y m_components.
         * It provides various mathematical operations and utility functions for vector manipulation.
         *
         * @tparam T The data type of the vector m_components.
         */
        template <class T>
        class ISLE_API Vector2
        {
        public:
            T x, y;

            /**
             * @brief Default constructor. Initializes the vector to (0, 0).
             */
            Vector2();

            /**
             * @brief Constructor with a single value. Initializes all m_components to the given value.
             *
             * @param xx The value to set all m_components to.
             */
            explicit Vector2(const T& xx);

            /**
             * @brief Constructor with individual component values.
             *
             * @param xx The x component value.
             * @param yy The y component value.
             */
            Vector2(const T& xx, const T& yy);

            /**
             * @brief Constructor with copy of component values of other Vectors.
             *
             * @param v The other vector.
             */
            Vector2(const Vector2<T>& v);
            /**
             * @brief Destructor.
             */
            ~Vector2();

            /**
             * @brief normalize the vector, making its magnitude 1.
             *
             * @return Reference to the normalized vector.
             */
            void normalize();

            /**
             * @brief Check if the vector is normalized (magnitude is approximately 1).
             *
             * @return True if the vector is normalized, otherwise false.
             */
            bool isNormalized();

            /**
             * @brief Calculate the Euclidean distance between two vectors.
             *
             * @param v The other vector.
             * @return The distance between this vector and v.
             */
            T distance(const Vector2<T>& v);

            /**
             * @brief Calculate the dot product between this vector and another vector.
             *
             * @param v The other vector.
             * @return The dot product of the two vectors.
             */
            T dotProduct(const Vector2<T>& v) const;

            /**
             * @brief Calculate the squared magnitude of the vector.
             *
             * @return The squared magnitude of the vector.
             */
            T squaredMagnitude();

            /**
             * @brief Calculate the magnitude (length) of the vector.
             *
             * @return The magnitude of the vector.
             */
            T magnitude();

            /**
             * @brief Predefined vector representing the up direction (0, 1).
             */
            static const Vector2<T> up;

            /**
             * @brief Predefined vector representing the right direction (1, 0).
             */
            static const Vector2<T> right;

            /**
             * @brief Predefined vector representing the zero vector (0, 0).
             */
            static const Vector2<T> zero;

            /**
             * @brief Predefined vector representing the one vector (1, 1).
             */
            static const Vector2<T> one;

            /**
             * @brief Predefined vector representing the up direction (0, -1).
             */
            static const Vector2<T> down;

            /**
             * @brief Predefined vector representing the right direction (-1, 0).
             */
            static const Vector2<T> left;

            Vector2<T> operator*(const T& s) const;
            Vector2<T> operator*=(const T& s);
            Vector2<T> operator/(const T& s) const;
            Vector2<T> operator/=(const T& s);
            Vector2<T> operator+(const Vector2<T>& v) const;
            Vector2<T> operator+=(const Vector2<T>& v);
            Vector2<T> operator-(const Vector2<T>& v) const;
            Vector2<T> operator-=(const Vector2<T>& v);
            bool operator==(const Vector2<T>& v) const;

            T* getRaw();
            explicit operator T*() { return &x; }
        private:
        };

        template<class T>
        T *Vector2<T>::getRaw() {
            return &x;
        }

        template <class T>
        Vector2<T>::Vector2() : x(T(0)), y(T(0)) {

        }

        template <class T>
        Vector2<T>::Vector2(const T& xx) : x(xx), y(xx) {

        }

        template <class T>
        Vector2<T>::Vector2(const T& xx, const T& yy) : x(xx), y(yy) {

        }

        template <class T>
        Vector2<T>::Vector2(const Vector2<T>& v) : x(v.x), y(v.y){

        }

        template <class T>
        Vector2<T>::~Vector2() = default;

        template <class T>
        void Vector2<T>::normalize() {
            T magSquared = ((x * x) + (y * y));
            if (magSquared > Epsilon<T> && std::abs((magSquared - T(1))) > Epsilon<T>) {
                T mag = 1/std::sqrt(magSquared);
                x *= mag;
                y *= mag;
            }
        }

        template <class T>
        bool Vector2<T>::isNormalized() {
            if (T(magnitude()) == 1) {
                return true;
            }
            else {
                return false;
            }
        }

        template <class T>
        T Vector2<T>::distance(const Vector2<T>& v) {
            return Vector2<T>(v.x - x, v.y - y).magnitude();
        }

        template <class T>
        T Vector2<T>::dotProduct(const Vector2<T>& v) const {
            return ((x * v.x) + (y * v.y));
        }

        template <class T>
        T Vector2<T>::squaredMagnitude() {
            return ((x * x) + (y * y));
        }

        template <class T>
        T Vector2<T>::magnitude() {
            return (sqrt((*this).squaredMagnitude()));
        }

        template <class T>
        const Vector2<T> Vector2<T>::zero = Vector2<T>(T(0), T(0));

        template <class T>
        const Vector2<T> Vector2<T>::one = Vector2<T>(T(1), T(1));

        template <class T>
        const Vector2<T> Vector2<T>::up = Vector2<T>(T(0), T(1));

        template <class T>
        const Vector2<T> Vector2<T>::right = Vector2<T>(T(1), T(0));

        template <class T>
        const Vector2<T> Vector2<T>::down = Vector2<T>(T(0), T(-1));

        template <class T>
        const Vector2<T> Vector2<T>::left = Vector2<T>(T(-1), T(0));

        template <class T>
        Vector2<T> Vector2<T>::operator*(const T& s) const {
            return Vector2<T>((x * s), (y * s));
        }

        template <typename T>
        Vector2<T> operator*(const T& s, const Vector2<T>& vec) {
            return Vector2<T>(vec.x * s, vec.y * s);
        }


        template<class T>
        Vector2<T> Vector2<T>::operator*=(const T &s) {
            x *= s;
            y *= s;
            return *this;
        }

        template <typename T>
        Vector2<T> operator*=(const T& s, Vector2<T>& vec) {
            vec.x *= s;
            vec.y *= s;
            return vec;
        }

        template <class T>
        Vector2<T> Vector2<T>::operator/(const T& s) const {
            return Vector2<T>((x / s), (y / s));
        }

        template <typename T>
        Vector2<T> operator/(const T& s, const Vector2<T>& vec) {
            return Vector2<T>(vec.x / s, vec.y / s);
        }

        template<class T>
        Vector2<T> Vector2<T>::operator/=(const T &s) {
            x /= s;
            y /= s;
            return *this;
        }

        template <typename T>
        Vector2<T> operator/=(const T& s, Vector2<T>& vec) {
            vec.x /= s;
            vec.y /= s;
            return vec;
        }

        template <class T>
        Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const {
            return Vector2<T>((x + v.x), (y + v.y));
        }

        template <class T>
        Vector2<T> operator+(const Vector2<T>& u, const Vector2<T>& v) {
            return Vector2<T>((u.x + v.x), (u.y + v.y));
        }

        template<class T>
        Vector2<T> Vector2<T>::operator+=(const Vector2<T> &v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        template<class T>
        Vector2<T> operator+=(Vector2<T>& u, const Vector2<T> &v) {
            u.x += v.x;
            u.y += v.y;
            return u;
        }

        template <class T>
        Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const {
            return Vector2<T>((x - v.x), (y - v.y));
        }

        template <class T>
        Vector2<T> operator-(const Vector2<T>& u, const Vector2<T>& v) {
            return Vector2<T>((u.x - v.x), (u.y - v.y));
        }

        template<class T>
        Vector2<T> Vector2<T>::operator-=(const Vector2<T> &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        template <class T>
        Vector2<T> operator-=(Vector2<T>& u, const Vector2<T>& v) {
            u.x -= v.x;
            u.y -= v.y;
            return u;
        }

        template<class T>
        bool Vector2<T>::operator==(const Vector2<T> &v) const {
            return (x == v.x) && (y == v.y);
        }

        template<class T>
        bool operator==(const Vector2<T>& u, const Vector2<T> &v) {
            return (u.x == v.x) && (u.y == v.y);
        }

        template<class T>
        std::ostream& operator<<(std::ostream& stream, const Vector2<T>& v) {
            stream << "(" << v.x << ", " << v.y << ")\n";
            return stream;
        }

        typedef Vector2<int> Vector2i;
        typedef Vector2<float> Vector2f;
        typedef Vector2<double> Vector2d;
    }
