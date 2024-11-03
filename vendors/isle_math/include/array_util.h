#pragma once
#include <iostream>


    namespace isle_engine::utility
    {
        template<typename T>
        void print_array(const T* arr, int size, int start = 0, int end = -1, const char* sep = ", ", const char* end_line = "\n") noexcept;

        template<typename T>
        T product(const T*, int size, int start = 0, int end = -1);

        template<typename T>
        void copy_array(T* dest, const T *src, int size, int start = 0, int end = -1);

        template<typename T>
        bool compare_array(const T* arr_1, const T* arr_2, int size);
    }

template<typename T>
void isle_engine::utility::print_array(const T* arr, int size, int start, int end, const char*  sep, const char* end_line) noexcept {
    if (end < 0) end = size;

    std::cout << "[";

    for (int i = start; i < end - 1; i++)
    {
        std::cout << arr[i] << sep;
    }

    std::cout << arr[end - 1] << "]" << end_line;
}

/**
 * @brief Product of all elements in an array
 * @param arr
 * @param size
 * @param start
 * @param end
 * @return int
 */
template<typename T>
T isle_engine::utility::product(const T* arr, int size, int start, int end)
{
    if (end < 0) end = size;
    T p = 1;

    for (int i = start; i < end; i++)
    {
        p *= arr[i];
    }

    return p;
}

/**
 * @brief Copy the content of arr to m_arr arrays
 * @param dest
 * @param src
 * @param size
 * @param start
 * @param end
 */
template<typename T>
void isle_engine::utility::copy_array(T* dest, const T *src, int size, int start, int end)
{
    if (end < 0) end = size;

    for (int i = start; i < end; i++)
    {
        dest[i] = src[i];
    }
}

