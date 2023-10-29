//
// Created by Eniola Olawale on 9/17/2023.
//

#pragma once
#include <cmath>
#include <iostream>

namespace pnt::math
{
    template<class T>
    struct Vector2{
        T x, y;
        Vector2();
        Vector2(T xx,T yy);
        explicit Vector2(T xx);
        Vector2(const Vector2<T>& v);
        ~Vector2();

        static T Distance(const Vector2 <T> &_this, const Vector2 <T> &other);
        Vector2<T> operator+(const Vector2<T>& other) const;
        Vector2<T> operator-(const Vector2<T>& other) const;
        Vector2<T> operator*(float s) const;
        Vector2<T> operator/(float s) const;
        Vector2<T>& operator+=(const Vector2<T>& other);
        Vector2<T>& operator-=(const Vector2<T>& other);
        Vector2<T>& operator*=(float s);
        Vector2<T>& operator/=(float s);
    };

    template<class T>
    std::ostream& operator<<(std::ostream& stream, const Vector2<T>& v) {
        stream << "(" << v.x << ", " << v.y << ")\n";
        return stream;
    }

    template<class T>
    Vector2<T>::Vector2() {
        x = T(0);
        y = T(0);
    }

    template<class T>
    Vector2<T>::Vector2(T xx, T yy) : x(T(xx)), y(T(yy)){

    }

    template<class T>
    Vector2<T>::Vector2(T xx) : x(T(xx)), y(T(xx)){

    }

    template<class T>
    Vector2<T>::Vector2(const Vector2<T> &v) : x(v.x), y(v.y){

    }

    template<class T>
    Vector2<T>::~Vector2() = default;

    template<class T>
    T Vector2<T>::Distance(const Vector2<T>& _this, const Vector2<T>& other)
    {
        float x = (other.x - _this.x);
        float y = (other.y - _this.y);
        float d = std::sqrt((x*x) + (y*y));
        return d;
    }

    template<class T>
    Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const
    {
        return {x + other.x, y + other.y};
    }

    template<class T>
    Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const
    {
        return {x - other.x, y - other.y};
    }

    template<class T>
    Vector2<T> Vector2<T>::operator*(float s) const
    {
        return {x * s, y * s};
    }

    template<class T>
    Vector2<T> Vector2<T>::operator/(float s) const
    {
        if (s != 0) {
            return {x / s, y / s};
        } else {
            return *this;
        }
    }

    template<class T>
    Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    template<class T>
    Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    template<class T>
    Vector2<T>& Vector2<T>::operator*=(float s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    template<class T>
    Vector2<T>& Vector2<T>::operator/=(float s)
    {
        if (s != 0) {
            x /= s;
            y /= s;
        }
        return *this;
    }

    template<class T>
    Vector2<T> operator*(float s, const Vector2<T>& v)
    {
        return {v.x * s, v.y * s};
    }
}


