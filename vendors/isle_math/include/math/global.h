#pragma once
#include "isle_pch.h"


    namespace isle_engine::math
    {
        /**
         * @brief Predefined Attribute representing the value of PI.
         */
        template <typename T>
        constexpr T PI = static_cast<T>(3.14159265358979323846);

        /**
         * @brief Predefined Attribute for converting angle from Radians to Degrees.
         */
        template <typename T>
        const T RadiansToDegrees = static_cast<T>(180) / PI<T>;

        /**
         * @brief Predefined Attribute for converting angle from Degrees to Radians.
         */
        template <typename T>
        const T DegreesToRadians = PI<T> / static_cast<T>(180);

        /**
         * @brief Predefined Attribute for epsilon.
         */
        template <typename T>
        constexpr T Epsilon = std::numeric_limits<T>::epsilon(); // This very little number handles round up issues.

    }

