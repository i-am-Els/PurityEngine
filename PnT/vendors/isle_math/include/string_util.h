#pragma once
#include <iostream>
#include <string>

namespace isle_engine::utility
{
    static std::string repeat(const std::string &str, size_t times) noexcept;
    static std::string justify_right(const std::string &str, size_t width, const std::string &fill = " ") noexcept;
    static std::string justify_left(const std::string &str, size_t width, const std::string &fill = " ") noexcept;
    static std::string justify_center(const std::string &str, size_t width, const std::string &fill = " ") noexcept;

}
    std::string isle_engine::utility::repeat(const std::string &str, size_t times) noexcept {
        std::string repeat_str;
        for (int i = 0; i < times; i++)
        {
            repeat_str += str;
        }
        return repeat_str;
    }

    /**
     * @brief Left justify string
     * @param str
     * @param width
     * @param fill
     * @return std::string
     */
    std::string isle_engine::utility::justify_left(const std::string &str, size_t width, const std::string &fill) noexcept {
        size_t rem = width - str.length();
        // if (rem < 0) rem = 0;
        return (str + repeat(fill, rem));
    }

    /**
     * @brief Right justify string
     * @param str
     * @param width
     * @param fill
     * @return std::string
     */
    std::string isle_engine::utility::justify_right(const std::string &str, size_t width, const std::string &fill) noexcept {
        size_t rem = width - str.length();
        return (repeat(fill, rem) + str);
    }

    /**
     * @brief Justify Center
     * @param str
     * @param width
     * @param fill
     * @return std::string
     */
    std::string isle_engine::utility::justify_center(const std::string &str, size_t width, const std::string &fill) noexcept {
        size_t rem = width - str.length();
        size_t mid = rem / 2;
        size_t rest = rem - mid;
        return (repeat(fill, rest) + str + repeat(fill, mid));
    }
