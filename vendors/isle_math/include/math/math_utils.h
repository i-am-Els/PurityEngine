//
// Created by Eniola Olawale on 10/13/2023.
//

#pragma once

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace isle_engine::math
{

    // =============================== REFLECT =====================================

    /**
     * @brief Calculate the reflected vector of an incident vector.
     *
     * @param Vector4<T> Incident vector
     * @param Vector4<T> Normal vector
     * @tparam T the type of the m_components of the vectors(This should be consistent)
     * @return The Reflected vector.
     */
    template<class T>
    Vector4<T> reflect(const Vector4<T> &incident, const Vector4<T>& normal) {
        return Vector4<T>(incident - (2 * dotProduct(normal, incident) * normal));
    }

    /**
     * @brief Calculate the reflected vector of an incident vector.
     *
     * @param Vector3<T> Incident vector
     * @param Vector3<T> Normal vector
     * @tparam T the type of the m_components of the vectors(This should be consistent)
     * @return The Reflected vector.
     */
    template<class T>
    Vector3<T> reflect(const Vector3<T> &incident, const Vector3<T>& normal) {
        return Vector3<T>(incident - (2 * dotProduct(normal, incident) * normal));
    }

    /**
     * @brief Calculate the reflected vector of an incident vector.
     *
     * @param Vector2<T> Incident vector
     * @param Vector2<T> Normal vector
     * @tparam T the type of the m_components of the vectors(This should be consistent)
     * @return The Reflected vector.
     */
    template<class T>
    Vector2<T> reflect(const Vector2<T> &incident, const Vector2<T>& normal) {
        return Vector2<T>(incident - (2 * dotProduct(normal, incident) * normal));
    }

    // =============================== REFRACT =====================================

    /**
     * @brief Calculate the refracted vector of an incident vector.
     *
     * @param Vector4<T> Incident vector
     * @param Vector4<T> Normal vector
     * @param T ratio of indices of refraction
     * @tparam T the type of the m_components of the vectors(This should be consistent)
     * @return The Refracted vector.
     */
    template<class T>
    Vector4<T> refract(const Vector4<T> &incident, const Vector4<T> &normal, T eta) {
        T k = T(1) - eta * eta * (T(1) - dotProduct(normal, incident) * dotProduct(normal, incident));
        if (k < T(0))
            return Vector4<T>();
        else
            return  eta * incident - (eta * dotProduct(normal, incident) + std::sqrt(k)) * normal;
    }

    /**
     * @brief Calculate the refracted vector of an incident vector.
     *
     * @param Vector3<T> Incident vector
     * @param Vector3<T> Normal vector
     * @param T ratio of indices of refraction
     * @tparam T the type of the m_components of the vectors(This should be consistent)
     * @return The Refracted vector.
     */
    template<class T>
    Vector3<T> refract(const Vector3<T> &incident, const Vector3<T> &normal, T eta) {
        T k = T(1) - eta * eta * (T(1) - dotProduct(normal, incident) * dotProduct(normal, incident));
        if (k < T(0))
            return Vector3<T>::zero;
        else
            return  eta * incident - (eta * dotProduct(normal, incident) + std::sqrt(k)) * normal;
    }

    /**
     * @brief Calculate the refracted vector of an incident vector.
     *
     * @param Vector2<T> Incident vector
     * @param Vector2<T> Normal vector
     * @param T ratio of indices of refraction
     * @tparam T the type of the m_components of the vectors(This should be consistent)
     * @return The Refracted vector.
     */
    template<class T>
    Vector2<T> refract(const Vector2<T> &incident, const Vector2<T> &normal, T eta) {
        T k = T(1) - eta * eta * (T(1) - dotProduct(normal, incident) * dotProduct(normal, incident));
        if (k < T(0))
            return Vector2<T>::zero;
        else
            return  eta * incident - (eta * dotProduct(normal, incident) + std::sqrt(k)) * normal;
    }

    // =============================== LERP CLAMPED =====================================

    /**
     * @brief Calculate the linear interpolation of a value between start vector and end vector.
     *
     * @param a The start vector.
     * @param b The end vector.
     * @param t a float between 0 and 1.
     * @return A vector signifying the interpolated value.
     */
    template <class T>
    Vector4<T> lerp(const Vector4<T>& a, const Vector4<T>& b, float t) {
        t = (std::max)(0.0f, (std::min)(1.0f, t));
        return (1 - t) * a + t * b;
    }

    /**
     * @brief Calculate the linear interpolation of a value between start vector and end vector.
     *
     * @param a The start vector.
     * @param b The end vector.
     * @param t a float between 0 and 1.
     * @return A vector signifying the interpolated value.
     */
    template <class T>
    Vector3<T> lerp(const Vector3<T>& a, const Vector3<T>& b, float t) {
        t = (std::max)(0.0f, (std::min)(1.0f, t));
        return (1 - t) * a + t * b;
    }

    /**
     * @brief Calculate the linear interpolation of a value between start vector and end vector.
     *
     * @param a The start vector.
     * @param b The end vector.
     * @param t a float between 0 and 1.
     * @return A vector signifying the interpolated value.
     */
    template <class T>
    Vector2<T> lerp(const Vector2<T>& a, const Vector2<T>& b, float t) {
        t = (std::max)(0.0f, (std::min)(1.0f, t));
        return (1 - t) * a + t * b;
    }

    // =============================== LERP UNCLAMPED =====================================

    /**
     * @brief Calculate the linear interpolation of a value between start vector and end vector.
     *
     * @param a The start vector.
     * @param b The end vector.
     * @param t a floating point value not limited by a range.
     * @return A vector signifying the interpolated value.
     */
    template <class T>
    Vector4<T> lerpUnclamped(const Vector4<T>& a, const Vector4<T>& b, float t) {
        return (1 - t) * a + t * b;
    }

    /**
     * @brief Calculate the linear interpolation of a value between start vector and end vector.
     *
     * @param a The start vector.
     * @param b The end vector.
     * @param t a floating point value not limited by a range.
     * @return A vector signifying the interpolated value.
     */
    template <class T>
    Vector3<T> lerpUnclamped(const Vector3<T>& a, const Vector3<T>& b, float t) {
        return (1 - t) * a + t * b;
    }

    /**
     * @brief Calculate the linear interpolation of a value between start vector and end vector.
     *
     * @param a The start vector.
     * @param b The end vector.
     * @param t a floating point value not limited by a range.
     * @return A vector signifying the interpolated value.
     */
    template <class T>
    Vector2<T> lerpUnclamped(const Vector2<T>& a, const Vector2<T>& b, float t) {
        return (1 - t) * a + t * b;
    }

    // =============================== MAGNITUDE =====================================
    /**
     * @brief Method that calculates the magnitude (length) of the vector v.
     *
     * @param v The vector.
     * @return The magnitude of v.
     */
    template <class T>
    T magnitude(const Vector4<T>& v) {
        return (sqrt(((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w))));
    }

    /**
     * @brief Method that calculates the magnitude (length) of the vector v.
     *
     * @param v The vector.
     * @return The magnitude of v.
     */
    template <class T>
    T magnitude(const Vector3<T>& v) {
        return (sqrt(((v.x * v.x) + (v.y * v.y) + (v.z * v.z) )));
    }

    /**
     * @brief Method that calculates the magnitude (length) of the vector v.
     *
     * @param v The vector.
     * @return The magnitude of v.
     */
    template <class T>
    T magnitude(const Vector2<T>& v) {
        return (sqrt(((v.x * v.x) + (v.y * v.y))));
    }

    // =============================== SQUARED MAGNITUDE =====================================

    /**
     * @brief Method that calculates the squared magnitude of the vector v.
     *
     * @param v The vector.
     * @return The squared magnitude of v.
     */
    template <class T>
    T squaredMagnitude(const Vector4<T>& v) {
        return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
    }

    /**
     * @brief Method that calculates the squared magnitude of the vector v.
     *
     * @param v The vector.
     * @return The squared magnitude of v.
     */
    template <class T>
    T squaredMagnitude(const Vector3<T>& v) {
        return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    }

    /**
     * @brief Method that calculates the squared magnitude of the vector v.
     *
     * @param v The vector.
     * @return The squared magnitude of v.
     */
    template <class T>
    T squaredMagnitude(const Vector2<T>& v) {
        return ((v.x * v.x) + (v.y * v.y));
    }

    // =============================== DISTANCE =====================================

    /**
     * @brief Method that calculates the Euclidean distance between two vectors.
     *
     * @param u The From vector.
     * @param v The To vector.
     * @return A scalar distance between this vector and v.
     */
    template <class T>
    T distance(const Vector4<T>& u, const Vector4<T>& v) {
        return Vector4<T>(v.x - u.x, v.y - u.y, v.z - u.z, v.w - u.w).magnitude();
    }

    /**
     * @brief Method that calculates the Euclidean distance between two vectors.
     *
     * @param u The From vector.
     * @param v The To vector.
     * @return A scalar distance between this vector and v.
     */
    template <class T>
    T distance(const Vector3<T>& u, const Vector3<T>& v) {
        return Vector3<T>(v.x - u.x, v.y - u.y, v.z - u.z).magnitude();
    }

    /**
     * @brief Method that calculates the Euclidean distance between two vectors.
     *
     * @param u The From vector.
     * @param v The To vector.
     * @return A scalar distance between this vector and v.
     */
    template <class T>
    T distance(const Vector2<T>& u, const Vector2<T>& v) {
        return Vector2<T>(v.x - u.x, v.y - u.y).magnitude();
    }

    // =============================== DOT PRODUCT =====================================

    /**
     * @brief Method that calculates the dot product between two vectors.
     *
     * @param u The first vector.
     * @param v The second vector.
     * @return A scalar resulting from dot product of the two vectors.
     */
    template <class T>
    T dotProduct(const Vector4<T>& u, const Vector4<T>& v) {
        return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w * v.w));
    }

    /**
     * @brief Method that calculates the dot product between two vectors.
     *
     * @param u The first vector.
     * @param v The second vector.
     * @return A scalar resulting from dot product of the two vectors.
     */
    template <class T>
    T dotProduct(const Vector3<T>& u, const Vector3<T>& v) {
        return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
    }

    /**
     * @brief Method that calculates the dot product between two vectors.
     *
     * @param u The first vector.
     * @param v The second vector.
     * @return A scalar resulting from dot product of the two vectors.
     */
    template <class T>
    T dotProduct(const Vector2<T>& u, const Vector2<T>& v) {
        return ((u.x * v.x) + (u.y * v.y));
    }

    // =============================== NORMALIZE =====================================
    // 4D

    /**
     * @brief Method that normalizes a vector in place, making its magnitude 1.
     *
     * @param v The vector.
     */
    template <class T>
    void normalize(const Vector4<T>& v) {
        T magSquared = ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
        if (magSquared > Epsilon<T> && std::abs((magSquared - T(1))) > Epsilon<T>) {
            T mag = 1/std::sqrt(magSquared);
            v.x *= mag;
            v.y *= mag;
            v.z *= mag;
            v.w *= mag;
        }
    }

    /**
    * @brief Method that returns a normalized vector.
    *
    * @param v The vector.
    * @return Vector4<T> normalized vector.
    */
    template <class T>
    Vector4<T> normalize_(Vector4<T> v){
        T vMagSquared = ((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
        if (vMagSquared > Epsilon<T> && (std::abs((vMagSquared - T(1)))) > Epsilon<T>) {
            T inv_mag = 1 / std::sqrt(vMagSquared);
            return Vector4<T>(
                    v.x * inv_mag,
                    v.y * inv_mag,
                    v.z * inv_mag,
                    v.w * inv_mag
            );
        }
        else
            return v;
    }

    /**
     * @brief Method that checks if a vector is normalized (magnitude is approximately 1).
     *
     * @param v The vector.
     * @return True if the vector is normalized, otherwise false.
     */
    template <class T>
    bool normalized(Vector4<T> v) {
        if (v.magnitude() == 1) {
            return true;
        }
        else {
            return false;
        }
    }

    //3D
    /**
     * @brief Method that normalizes a vector in place, making its magnitude 1.
     *
     * @param v The vector.
     */
    template <class T>
    void normalize(const Vector3<T>& v) {
        T magSquared = ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
        if (magSquared > Epsilon<T> && std::abs((magSquared - T(1))) > Epsilon<T>) {
            T mag = 1/std::sqrt(magSquared);
            v.x *= mag;
            v.y *= mag;
            v.z *= mag;
        }
    }

    /**
    * @brief Method that returns a normalized vector.
    *
    * @param v The vector.
    * @return Vector3<T> normalized vector.
    */
    template <class T>
    Vector3<T> normalize_(Vector3<T> v){
        T vMagSquared = ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
        if (vMagSquared > Epsilon<T> && (std::abs((vMagSquared - T(1)))) > Epsilon<T>) {
            T inv_mag = 1 / std::sqrt(vMagSquared);
            return Vector3<T>(
                    v.x * inv_mag,
                    v.y * inv_mag,
                    v.z * inv_mag
            );
        }
        else
            return v;
    }

    /**
     * @brief Method that checks if a vector is normalized (magnitude is approximately 1).
     *
     * @param v The vector.
     * @return True if the vector is normalized, otherwise false.
     */
    template <class T>
    bool normalized(Vector3<T> v) {
        if (v.magnitude() == 1) {
            return true;
        }
        else {
            return false;
        }
    }

    //2D
    /**
     * @brief Method that normalizes a vector in place, making its magnitude 1.
     *
     * @param v The vector.
     */
    template <class T>
    void normalize(const Vector2<T>& v) {
        T magSquared = ((v.x * v.x) + (v.y * v.y));
        if (magSquared > Epsilon<T> && std::abs((magSquared - T(1))) > Epsilon<T>) {
            T mag = 1/std::sqrt(magSquared);
            v.x *= mag;
            v.y *= mag;
        }
    }

    /**
    * @brief Method that returns a normalized vector.
    *
    * @param v The vector.
    * @return Vector2<T> normalized vector.
    */
    template <class T>
    Vector2<T> normalize_(Vector2<T> v){
        T vMagSquared = ((v.x * v.x) + (v.y * v.y));
        if (vMagSquared > Epsilon<T> && (std::abs((vMagSquared - T(1)))) > Epsilon<T>) {
            T inv_mag = 1 / std::sqrt(vMagSquared);
            return Vector2<T>(
                    v.x * inv_mag,
                    v.y * inv_mag
            );
        }
        else
            return v;
    }

    /**
     * @brief Method that checks if a vector is normalized (magnitude is approximately 1).
     *
     * @param v The vector.
     * @return True if the vector is normalized, otherwise false.
     */
    template <class T>
    bool normalized(Vector2<T> v) {
        if (v.magnitude() == 1) {
            return true;
        }
        else {
            return false;
        }
    }

    // =============================== ANGLE BETWEEN =====================================

    /**
     * @brief Method that calculates the angle (in radians) between two vectors.
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Angle (in radians) of type T.
     */
    template <class T>
    T angleBetween(const Vector4<T>& a, const Vector4<T>& b) {
        T dot = dotProduct(a, b);
        T aMag = magnitude(a);
        T bMag = magnitude(b);

        if (aMag == 0 || bMag == 0) {
            return 0;  // If either vector is a zero vector, angle is 0
        }

        T cosAngle = dot / (aMag * bMag);

        // clamp between the valid range for cos theta...
        cosAngle = std::min<T>(1, std::max<T>(-1, cosAngle));

        T angle = std::acos(cosAngle);
        return angle;
    }

    /**
     * @brief Method that calculates the angle (in radians) between two vectors.
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Angle (in radians) of type T.
     */
    template <class T>
    T angleBetween(const Vector3<T>& a, const Vector3<T>& b) {
        T dot = dotProduct(a, b);
        T aMag = magnitude(a);
        T bMag = magnitude(b);

        if (aMag == 0 || bMag == 0) {
            return 0;  // If either vector is a zero vector, angle is 0
        }

        T cosAngle = dot / (aMag * bMag);

        // clamp between the valid range for cos theta...
        cosAngle = std::min<T>(1, std::max<T>(-1, cosAngle));

        T angle = std::acos(cosAngle);
        return angle;
    }

    /**
     * @brief Method that calculates the angle (in radians) between two vectors.
     *
     * @param a The first vector.
     * @param b The second vector.
     * @return Angle (in radians) of type T.
     */
    template <class T>
    T angleBetween(const Vector2<T>& a, const Vector2<T>& b) {
        T dot = dotProduct(a, b);
        T aMag = magnitude(a);
        T bMag = magnitude(b);

        if (aMag == 0 || bMag == 0) {
            return 0;  // If either vector is a zero vector, angle is 0
        }

        T cosAngle = dot / (aMag * bMag);

        // clamp between the valid range for cos theta...
        cosAngle = std::min<T>(1, std::max<T>(-1, cosAngle));

        T angle = std::acos(cosAngle);
        return angle;
    }

    // =============================== CROSS PRODUCT =====================================

    /**
     * @brief Method that calculates the cross product between two vectors.
     *
     * @param u The first vector.
     * @param v The second vector.
     * @return A vector of the cross product of the two vectors.
     */
    template <class T>
    Vector3<T> crossProduct(const Vector3<T>& u, const Vector3<T>& v) {
        return Vector3<T>(
                ((u.y * v.z) - (u.z * v.y)),
                ((u.z * v.x) - (u.x * v.z)),
                ((u.x * v.y) - (u.y * v.x))
        );
    }

}
