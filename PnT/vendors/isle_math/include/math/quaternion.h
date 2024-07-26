//
// Created by Eniola Olawale on 9/18/2023.
//

#pragma once
#include "core.h"
#include "vector3.h"
#include "global.h"
#include "math_utils.h"
#include "matrixNM.h"


    namespace isle_engine::math
    {
        template<class T>
        class ISLE_API Quaternion {
        public:
            Quaternion();
            Quaternion(T ww, T xx, T yy, T zz);
            Quaternion(const Quaternion<T>& q);
            Quaternion(T angle, const Vector3<T>& axis);
            ~Quaternion() = default;


            Quaternion<T>& operator=(const Quaternion<T>& q);
            Quaternion<T> operator*(const Quaternion<T>& q) const;
            Quaternion<T> operator*=(const Quaternion<T>& q) const;
            Quaternion<T> operator*(T s);
            Quaternion<T> operator*=(T s);
            Quaternion<T> operator+(const Quaternion<T>& q) const;
            Quaternion<T> operator+=(const Quaternion<T>& q) const;
            Quaternion<T> operator-(const Quaternion<T>& q) const;
            Quaternion<T> operator-=(const Quaternion<T>& q) const;


            void negate();
            static Quaternion<T> s_slerp(const Quaternion<T>& q, const Quaternion<T>& p, T t);
            Quaternion<T> conjugate();
            Quaternion<T> inverse();
            void normalize();
            static T s_dot(const Quaternion<T>& q, const Quaternion<T>& p);
            static Quaternion<T> s_difference(const Quaternion<T>& q, const Quaternion<T>& p);
            static Quaternion<T> s_createIdentity();

            static Vector3<T> s_rotate(const Quaternion<T>& q, const Vector3<T>& v);

            // Set Look Rotation Method or LookAtTarget(Vector targetDir);

            T w, x, y, z;

        private:
            static inline Quaternion<T> s_multiply(const Quaternion<T>& q, const Quaternion<T>& p);
        };



        // --------------------------------------- DEFINITIONS ---------------------------------------------
        // Constructors
        // .................................................................................................

        template<class T>
        Quaternion<T>::Quaternion() : w(T(0)), x(T(0)), y(T(0)), z(T(0)) {

        }

        template<class T>
        Quaternion<T>::Quaternion(T ww, T xx, T yy, T zz) : w(T(ww)), x(T(xx)), y(T(yy)), z(T(zz)) {
            // s_normalize the Quaternion
            normalize();
        }

        template<class T>
        Quaternion<T>::Quaternion(const Quaternion<T> &q)  : w(T(q.w)), x(T(q.x)), y(T(q.y)), z(T(q.z)) {
            // s_normalize the Quaternion
            normalize();
        }

        template<class T>
        Quaternion<T>::Quaternion(T angle, const Vector3<T>& axis){
            // Convert to w, x, y, z Notation
            // Axis in world coordinate space.
            // Note that you should convert the axis from object/local space to a vector in world space
            // since the basis assumed for this operation are the standard basis [1, 0 ,0], [0, 1, 0], [0, 0, 1].
            Vector3<T> v = isle_engine::math::normalize_(axis);
            angle /= 2;
            w = std::cos(angle);
            x = std::sin(angle) * v.x;
            y = std::sin(angle) * v.y;
            z = std::sin(angle) * v.z;
        }

        // End of Constructors
        // .................................................................................................


        // Operators
        // .................................................................................................

        template<class T>
        Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T> &q) {
            if (this == &q) {
                return *this;
            }

            Quaternion<T> temp(q);
            std::swap(*this, temp);
            return *this;
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> &q) const{
            return s_multiply(*this, q);
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator*=(const Quaternion<T> &q) const{
            *this = s_multiply(*this, q);
            return *this;
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator*(T s) {
            return Quaternion<T>(w * s, x * s, y * s, z * s);
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator*=(T s) {
            w *= s;
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator+(const Quaternion<T> &q) const{
            return Quaternion<T>(w + q.w, x + q.x, y + q.y, z + q.z);
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator+=(const Quaternion<T> &q) const{
            w += q.w;
            x += q.x;
            y += q.y;
            z += q.z;
            return *this;
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator-(const Quaternion<T> &q) const{
            return Quaternion<T>(w - q.w, x - q.x, y - q.y, z - q.z);
        }

        template<class T>
        Quaternion<T> Quaternion<T>::operator-=(const Quaternion<T> &q) const{
            w -= q.w;
            x -= q.x;
            y -= q.y;
            z -= q.z;
            return *this;
        }

        // End of Operators
        // .................................................................................................

        // Methods
        // .................................................................................................


        template<class T>
        void Quaternion<T>::negate() {
            w *= -1;
            x *= -1;
            y *= -1;
            z *= -1;
        }

        template<class T>
        Quaternion<T> Quaternion<T>::s_slerp(const Quaternion<T> &q, const Quaternion<T> &p, T t) {
            // Calculate Spherical Interpolation
            // (sin((1-t)*omega)/sin(omega))*q + (sin(t*omega)/sin(omega))*p
            Quaternion<T> s;

            T cosOmega = s_dot(q, p);

            // If the dot is negative, negate one of the quaternions to take the shortest route...
            if (cosOmega < T(0)){
                p.negate();
                cosOmega *= -1;
            }

            // constants
            T kQ, kP;

            // Check if they are close enough and just interpolate linearly
            if (cosOmega > 1 - Epsilon<T>){
                kQ = 1 - t;
                kP = t;
            }
            else{
                T omega = std::acos(cosOmega);
                T kInverseSinOmega = 1 / std::sin(omega);

                kQ = std::sin((1-t) * omega) * kInverseSinOmega;
                kP = std::sin(t * omega) * kInverseSinOmega;
            }
            s = (q * kQ) + (p * kP);
            return s;
        }

        template<class T>
        Quaternion<T> Quaternion<T>::conjugate() {
            // Perform and Return Conjugate
            return Quaternion<T>(w, -x, -y, -z);
        }

        template<class T>
        Quaternion<T> Quaternion<T>::inverse() {
            normalize();
            return conjugate();
        }

        template<class T>
        void Quaternion<T>::normalize() {
            T magSquared = ((w * w) + (x * x) + (y * y) + (z * z));
            if (magSquared > Epsilon<T> && (std::abs(magSquared - T(1))) > Epsilon<T>) {
                T mag = std::sqrt(magSquared);
                w /= mag;
                x /= mag;
                y /= mag;
                z /= mag;
            }
        }

        template<class T>
        T Quaternion<T>::s_dot(const Quaternion<T> &q, const Quaternion<T> &p) {
            return T((q.w * p.w) + (q.x * p.x) + (q.y * p.y) + (q.z * p.z));
        }

        template<class T>
        Quaternion<T> Quaternion<T>::s_difference(const Quaternion<T> &q, const Quaternion<T> &p) {
            Quaternion<T> d = p * q.inverse();
            return d;
        }

        template<class T>
        Quaternion<T> Quaternion<T>::s_createIdentity() {
            return Quaternion<T>(T(1), Vector3<T>::zero());
        }

        template<class T>
        Quaternion<T> Quaternion<T>::s_multiply(const Quaternion<T> &q, const Quaternion<T> &p) {
            return Quaternion<T>(
                    (q.w * p.w) - (q.x * p.x) - (q.y * p.y) - (q.z * p.z),
                    (q.w * p.x) + (q.x * p.w) + (q.y * p.z) - (q.z * p.y),
                    (q.w * p.y) + (q.y * p.w) + (q.z * p.x) - (q.x * p.z),
                    (q.w * p.z) + (q.z * p.w) + (q.x * p.y) - (q.y * p.x)
                    );
        }

        // End of Members
        // ...............................................................................................


        // Rotation Methods
        // ...............................................................................................

        template<class T>
        Vector3<T> Quaternion<T>::s_rotate(const Quaternion<T> &q, const Vector3<T> &v) {
            Quaternion<T> r_v = q * Quaternion<T>(T(0), v) * q.inverse();

            return Vector3<T>(r_v.x, r_v.y, r_v.z);
        }
    }

