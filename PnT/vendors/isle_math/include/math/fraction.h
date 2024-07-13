#pragma once
#include "core.h"


namespace isle_engine::math {

    class ISLE_API Fraction {
    private:
        int m_numerator;
        int m_denominator;

    public:
        int &numerator = m_numerator;
        int &denominator = m_denominator;

        Fraction();

        explicit Fraction(const int &value);

        Fraction(const int &numerator, const int &denominator);

        Fraction operator+(const Fraction &other) const;

        Fraction &operator+(const Fraction &other);

        static int gcd(int num1, int num2);

    };
}
