
#include "fraction.h"

namespace isle_engine::math{

    Fraction::Fraction(): m_numerator{0}, m_denominator{1}
    {
        ;
    }


    Fraction::Fraction(const int &value): m_numerator{value}, m_denominator{1}
    {
        ;
    }


    Fraction::Fraction(const int &numerator, const int &denominator)
    {
        int divisor = gcd(numerator, denominator);
        m_numerator = numerator/divisor;
        m_denominator = denominator/divisor;
    }


    int Fraction::gcd(int num1, int num2) {
        int temp;
        while (num2 != 0) {
            temp = num1;
            num1 = num2;
            num2 = temp % num2;
        }
        return num1;
    }


    Fraction Fraction::operator+(const Fraction &other) const {
        return {};
    }


    Fraction &Fraction::operator+(const Fraction &other) {
        return *this;
    }

}
