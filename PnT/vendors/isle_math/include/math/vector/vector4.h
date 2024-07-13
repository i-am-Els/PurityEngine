#pragma once
#include "core.h"
#include "global.h"


    namespace isle_engine::math
    {
        /**
         * @brief Represents a 4D vector.
         *
         * This class represents a 4D vector with x, y, z, and w m_components.
         * It provides various mathematical operations and utility functions for vector manipulation.
         *
         * @tparam T The data type of the vector m_components.
         */
        template <class T>
        class ISLE_API Vector4
        {
        public:
            T x, y, z, w;

            /**
             * @brief Default constructor. Initializes the vector to (0, 0, 0, 1).
             */
            Vector4();

            /**
             * @brief Constructor with a single value. Initializes all m_components to the given value.
             *
             * @param xx The value to set all m_components to.
             */
            explicit Vector4(const T& xx);

            /**
             * @brief Constructor with copy of component values of other Vectors.
             *
             * @param v The other vector.
             */
            Vector4(const Vector4<T>& v);

            /**
             * @brief Constructor with individual component values.
             *
             * @param xx The x component value.
             * @param yy The y component value.
             * @param zz The z component value.
             * @param ww The w component value.
             */
            Vector4(const T& xx, const T& yy, const T& zz, const T& ww = T(1));

            /**
             * @brief Destructor.
             */
            ~Vector4();

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
            T distance(const Vector4<T>& v);

            /**
             * @brief Calculate the dot product between this vector and another vector.
             *
             * @param v The other vector.
             * @return The dot product of the two vectors.
             */
            T dotProduct(const Vector4<T>& v) const;

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

            Vector4<T> operator*(const T& s) const;
            Vector4<T> operator*=(const T& s);
            Vector4<T> operator/(const T& s) const;
            Vector4<T> operator/=(const T& s);
            Vector4<T> operator+(const Vector4<T>& v) const;
            Vector4<T> operator+=(const Vector4<T>& v);
            Vector4<T> operator-(const Vector4<T>& v) const;
            Vector4<T> operator-=(const Vector4<T>& v);
            bool operator==(const Vector4<T>& v) const;

            T* getRaw();
            explicit operator T*() { return &x; }
        private:
        };

        template<class T>
        T *Vector4<T>::getRaw() {
            return &x;
        }

        template <class T>
        Vector4<T>::Vector4() : x(T(0)), y(T(0)), z(T(0)), w(T(1)) {

        }

        template <class T>
        Vector4<T>::Vector4(const T& xx) : x(xx), y(xx), z(xx), w(T(1)) {

        }

        template<class T>
        Vector4<T>::Vector4(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w){

        }

        template <class T>
        Vector4<T>::Vector4(const T& xx, const T& yy, const T& zz, const T& ww) : x(xx), y(yy), z(zz), w(ww) {

        }

        template <class T>
        Vector4<T>::~Vector4() = default;

        template <class T>
        void Vector4<T>::normalize() {
            T magSquared = ((x * x) + (y * y) + (z * z) + (w * w));
            if (magSquared > Epsilon<T> && std::abs((magSquared - T(1))) > Epsilon<T>) {
                T mag = 1/std::sqrt(magSquared);
                x *= mag;
                y *= mag;
                z *= mag;
                w *= mag;
            }
        }

        template <class T>
        bool Vector4<T>::isNormalized() {
            if (T(magnitude()) == 1) {
                return true;
            }
            else {
                return false;
            }
        }

        template <class T>
        T Vector4<T>::distance(const Vector4<T>& v) {
            return Vector4<T>(v.x - x, v.y - y, v.z - z, v.w - w).magnitude();
        }

        template <class T>
        T Vector4<T>::dotProduct(const Vector4<T>& v) const {
            return ((x * v.x) + (y * v.y) + (z * v.z) + (w * v.w));
        }

        template <class T>
        T Vector4<T>::squaredMagnitude() {
            return ((x * x) + (y * y) + (z * z) + (w * w));
        }

        template <class T>
        T Vector4<T>::magnitude() {
            return (sqrt((*this).squaredMagnitude()));
        }


        template <class T>
        Vector4<T> Vector4<T>::operator*(const T& s) const {
            return Vector4<T>((x * s), (y * s), (z * s), (w * s));
        }

        template <typename T>
        Vector4<T> operator*(const T& s, const Vector4<T>& vec) {
            return Vector4<T>(vec.x * s, vec.y * s, vec.z * s, vec.w * s);
        }

        template<class T>
        Vector4<T> Vector4<T>::operator*=(const T &s) {
            x *= s;
            y *= s;
            z *= s;
            w *= s;
            return *this;
        }

        template <typename T>
        Vector4<T> operator*=(const T& s, Vector4<T>& vec) {
            vec.x *= s;
            vec.y *= s;
            vec.z *= s;
            vec.w *= s;
            return vec;
        }

        template <class T>
        Vector4<T> Vector4<T>::operator/(const T& s) const {
            return Vector4<T>((x / s), (y / s), (z / s), (w / s));
        }

        template <typename T>
        Vector4<T> operator/(const T& s, const Vector4<T>& vec) {
            return Vector4<T>(vec.x / s, vec.y / s, vec.z / s, vec.w / s);
        }

        template<class T>
        Vector4<T> Vector4<T>::operator/=(const T &s) {
            x /= s;
            y /= s;
            z /= s;
            w /= s;
            return *this;
        }

        template <typename T>
        Vector4<T> operator/=(const T& s, Vector4<T>& vec) {
            vec.x /= s;
            vec.y /= s;
            vec.z /= s;
            vec.w /= s;
            return vec;
        }

        template <class T>
        Vector4<T> Vector4<T>::operator+(const Vector4<T>& v) const {
            return Vector4<T>((x + v.x), (y + v.y), (z + v.z), (w + v.w));
        }

        template <class T>
        Vector4<T> operator+(const Vector4<T>& u, const Vector4<T>& v) {
            return Vector4<T>((u.x + v.x), (u.y + v.y), (u.z + v.z), (u.w + v.w));
        }

        template<class T>
        Vector4<T> Vector4<T>::operator+=(const Vector4<T> &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }

        template<class T>
        Vector4<T> operator+=(Vector4<T>& u, const Vector4<T> &v) {
            u.x += v.x;
            u.y += v.y;
            u.z += v.z;
            u.w += v.w;
            return u;
        }

        template <class T>
        Vector4<T> Vector4<T>::operator-(const Vector4<T>& v) const {
            return Vector4<T>((x - v.x), (y - v.y), (z - v.z), (w - v.w));
        }

        template <class T>
        Vector4<T> operator-(const Vector4<T>& u, const Vector4<T>& v) {
            return Vector4<T>((u.x - v.x), (u.y - v.y), (u.z - v.z), (u.w - v.w));
        }

        template<class T>
        Vector4<T> Vector4<T>::operator-=(const Vector4<T> &v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        template <class T>
        Vector4<T> operator-=(Vector4<T>& u, const Vector4<T>& v) {
            u.x -= v.x;
            u.y -= v.y;
            u.z -= v.z;
            u.w -= v.w;
            return u;
        }

        template<class T>
        bool Vector4<T>::operator==(const Vector4<T> &v) const {
            return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
        }

        template<class T>
        bool operator==(const Vector4<T>& u, const Vector4<T> &v) {
            return (u.x == v.x) && (u.y == v.y) && (u.z == v.z) && (u.w == v.w);
        }

        template<class T>
        std::ostream& operator<<(std::ostream& stream, const Vector4<T>& v) {
            stream << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")\n";
            return stream;
        }

        typedef Vector4<int> Vector4i;
        typedef Vector4<float> Vector4f;
        typedef Vector4<double> Vector4d;
    }
