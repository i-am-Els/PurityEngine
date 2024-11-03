#pragma once
#include "core.h"
#include "global.h"


	namespace isle_engine::math
	{
		/**
		 * @brief Represents a 3D vector.
		 *
		 * This class represents a 3D vector with x, y, and z m_components.
		 * It provides various mathematical operations and utility functions for vector manipulation.
		 *
		 * @tparam T The data type of the vector m_components.
		 */
		template <class T>
		class ISLE_API Vector3
		{
		public:
			T x, y, z;

			/**
			 * @brief Default constructor. Initializes the vector to (0, 0, 0).
			 */
			Vector3();

			/**
			 * @brief Constructor with a single value. Initializes all m_components to the given value.
			 *
			 * @param xx The value to set all m_components to.
			 */
			explicit Vector3(const T& xx);

            /**
             * @brief Constructor with copy of component values of other Vectors.
             *
             * @param v The other vector.
             */
            Vector3(const Vector3<T>& v);
			/**
			 * @brief Constructor with individual component values.
			 *
			 * @param xx The x component value.
			 * @param yy The y component value.
			 * @param zz The z component value.
			 */
			Vector3(const T& xx, const T& yy, const T& zz);

			/**
			 * @brief Destructor.
			 */
			~Vector3();

			/**
			 * @brief normalize the vector in place, making its magnitude 1.
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
			T distance(const Vector3<T>& v);

			/**
			 * @brief Calculate the dot product between this vector and another vector.
			 *
			 * @param v The other vector.
			 * @return The dot product of the two vectors.
			 */
			T dotProduct(const Vector3<T>& v) const;

			/**
			 * @brief Calculate the cross product between this vector and another vector.
			 *
			 * @param v The other vector.
			 * @return The cross product of the two vectors.
			 */
			Vector3<T> crossProduct(const Vector3<T>& v) const;

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
			 * @brief Predefined vector representing the up direction (0, 1, 0).
			 */
//			static Vector3<T> up() { return Vector3<T>(T(0), T(1), T(0)); }
			static const Vector3<T> up;

			/**
			 * @brief Predefined vector representing the forward direction (0, 0, 1).
			 */
//			static Vector3<T> forward() { return Vector3<T>(T(0), T(0), T(1)); }
			static const Vector3<T> forward;

			/**
			 * @brief Predefined vector representing the right direction (1, 0, 0).
			 */
//			static Vector3<T> right() { return Vector3<T>(T(1), T(0), T(0)); }
			static const Vector3<T> right;

			/**
			 * @brief Predefined vector representing the zero vector (0, 0, 0).
			 */
//			static Vector3<T> zero() { return Vector3<T>(T(0), T(0), T(0)); }
			static const Vector3<T> zero;

			/**
			 * @brief Predefined vector representing the one vector (1, 1, 1).
			 */
//			static Vector3<T> one() { return Vector3<T>(T(1), T(1), T(1)); }
			static const Vector3<T> one;

			/**
			 * @brief Predefined vector representing the up direction (0, -1, 0).
			 */
//			static Vector3<T> down() { return Vector3<T>(T(0), T(-1), T(0)); }
			static const Vector3<T> down;

			/**
			 * @brief Predefined vector representing the forward direction (0, 0, -1).
			 */
//			static Vector3<T> back() { return Vector3<T>(T(0), T(0), T(-1)); }
			static const Vector3<T> back;

			/**
			 * @brief Predefined vector representing the right direction (-1, 0, 0).
			 */
//			static Vector3<T> left() { return Vector3<T>(T(-1), T(0), T(0)); }
			static const Vector3<T> left;

			Vector3<T> operator/(const T& s) const;
			Vector3<T> operator/=(const T& s);
			Vector3<T> operator*(const T& s) const;
			Vector3<T> operator*=(const T& s);
			Vector3<T> operator+(const Vector3<T>& v) const;
			Vector3<T> operator+=(const Vector3<T>& v);
			Vector3<T> operator-(const Vector3<T>& v) const;
            Vector3<T> operator-=(const Vector3<T>& v);
            bool operator==(const Vector3<T>& v) const;

            T* getRaw();
            explicit operator T*() { return &x; }
		private:
		};

        template<class T>
        T *Vector3<T>::getRaw() {
            return &x;
        }

        template<class T>
        Vector3<T>::Vector3(const Vector3<T> &v) : x(v.x) , y(v.y), z(v.z){

        }


        template <class T>
		Vector3<T>::Vector3() : x(T(0)), y(T(0)), z(T(0)) {

		}

		template <class T>
		Vector3<T>::Vector3(const T& xx) : x(xx), y(xx), z(xx) {

		}

		template <class T>
		Vector3<T>::Vector3(const T& xx, const T& yy, const T& zz) : x(xx), y(yy), z(zz) {

		}

		template <class T>
		Vector3<T>::~Vector3() = default;

		template <class T>
		void Vector3<T>::normalize() {
            T vMagSquared = ((x * x) + (y * y) + (z * z));
            if (vMagSquared > Epsilon<T> && std::abs((vMagSquared - T(1))) > Epsilon<T>)
            {
                T inv_mag = 1/std::sqrt(vMagSquared);
                x *= inv_mag;
                y *= inv_mag;
                z *= inv_mag;
            }
		}

		template <class T>
		bool Vector3<T>::isNormalized() {
			if (T(magnitude()) == 1) {
				return true;
			}
			else {
				return false;
			}
		}

		template <class T>
		T Vector3<T>::distance(const Vector3<T>& v) {
			return Vector3<T>(v.x - x, v.y - y, v.z - z).magnitude();
		}

		template <class T>
		T Vector3<T>::dotProduct(const Vector3<T>& v) const {
			return ((x * v.x) + (y * v.y) + (z * v.z));
		}

		template <class T>
		Vector3<T> Vector3<T>::crossProduct(const Vector3<T>& v) const {
			return Vector3<T>(
				((y * v.z) - (z * v.y)),
				((z * v.x) - (x * v.z)),
				((x * v.y) - (y * v.x))
			);
		}

		template <class T>
		T Vector3<T>::squaredMagnitude() {
			return ((x * x) + (y * y) + (z * z));
		}

		template <class T>
		T Vector3<T>::magnitude() {
			return (sqrt((*this).squaredMagnitude()));
		}

		template <class T>
		Vector3<T> Vector3<T>::operator*(const T& s) const {
			return Vector3<T>((x * s), (y * s), (z * s));
		}

		template <typename T>
		Vector3<T> operator*(const T& s, const Vector3<T>& vec) {
			return Vector3<T>(vec.x * s, vec.y * s, vec.z * s);
		}


        template<class T>
        Vector3<T> Vector3<T>::operator*=(const T &s) {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        template <typename T>
		Vector3<T> operator*=(const T& s, Vector3<T>& vec) {
            vec.x *= s;
            vec.y *= s;
            vec.z *= s;
			return vec;
        }

        template <class T>
		Vector3<T> Vector3<T>::operator/(const T& s) const {
			return Vector3<T>((x / s), (y / s), (z / s));
		}

		template <typename T>
		Vector3<T> operator/(const T& s, const Vector3<T>& vec) {
			return Vector3<T>(vec.x / s, vec.y / s, vec.z / s);
		}

        template<class T>
        Vector3<T> Vector3<T>::operator/=(const T &s) {
            x /= s;
            y /= s;
            z /= s;
            return *this;
        }

        template <typename T>
		Vector3<T> operator/=(const T& s, Vector3<T>& vec) {
            vec.x /= s;
            vec.y /= s;
            vec.z /= s;
			return vec;
		}

		template <class T>
		Vector3<T> Vector3<T>::operator+(const Vector3<T>& v) const {
			return Vector3<T>((x + v.x), (y + v.y), (z + v.z));
		}

        template <class T>
		Vector3<T> operator+(const Vector3<T>& u, const Vector3<T>& v) {
			return Vector3<T>((u.x + v.x), (u.y + v.y), (u.z + v.z));
		}

        template<class T>
        Vector3<T> Vector3<T>::operator+=(const Vector3<T> &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        template<class T>
        Vector3<T> operator+=(Vector3<T>& u, const Vector3<T> &v) {
            u.x += v.x;
            u.y += v.y;
            u.z += v.z;
            return u;
        }

		template <class T>
		Vector3<T> Vector3<T>::operator-(const Vector3<T>& v) const {
			return Vector3<T>((x - v.x), (y - v.y), (z - v.z));
		}

        template <class T>
        Vector3<T> operator-(const Vector3<T>& u, const Vector3<T>& v) {
            return Vector3<T>((u.x - v.x), (u.y - v.y), (u.z - v.z));
        }

        template<class T>
        Vector3<T> Vector3<T>::operator-=(const Vector3<T> &v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        template <class T>
        Vector3<T> operator-=(Vector3<T>& u, const Vector3<T>& v) {
            u.x -= v.x;
            u.y -= v.y;
            u.z -= v.z;
            return u;
        }

        template<class T>
        bool Vector3<T>::operator==(const Vector3<T> &v) const {
            return (x == v.x) && (y == v.y) && (z == v.z);
        }

        template<class T>
        bool operator==(const Vector3<T>& u, const Vector3<T> &v) {
            return (u.x == v.x) && (u.y == v.y) && (u.z == v.z);
        }

		template<class T>
		std::ostream& operator<<(std::ostream& stream, const Vector3<T>& v) {
			stream << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
			return stream;
		}


        template <class T>
        const Vector3<T> Vector3<T>::zero = Vector3<T>(T(0), T(0), T(0));

        template <class T>
        const Vector3<T> Vector3<T>::one = Vector3<T>(T(1), T(1), T(1));

        template <class T>
        const Vector3<T> Vector3<T>::up = Vector3<T>(T(0), T(1), T(0));

        template <class T>
        const Vector3<T> Vector3<T>::forward = Vector3<T>(T(0), T(0), T(1));

        template <class T>
        const Vector3<T> Vector3<T>::right = Vector3<T>(T(1), T(0), T(0));

        template <class T>
        const Vector3<T> Vector3<T>::down = Vector3<T>(T(0), T(-1), T(0));

        template <class T>
        const Vector3<T> Vector3<T>::back = Vector3<T>(T(0), T(0), T(-1));

        template <class T>
        const Vector3<T> Vector3<T>::left = Vector3<T>(T(-1), T(0), T(0));

		typedef Vector3<int> Vector3i;
		typedef Vector3<float> Vector3f;
		typedef Vector3<double> Vector3d;

    }
