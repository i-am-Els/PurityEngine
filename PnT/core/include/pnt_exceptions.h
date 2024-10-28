//
// Created by Eniola Olawale on 9/14/2024.
//

#pragma once


#include "core_macros.h"


namespace pnt::exceptions
{
    class PNT_API NullBufferError final : public std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override{
            return "Buffer pointer is a null pointer";
        }
    };

    class PNT_API NullPointerError final : public std::exception
    {
    public:
        operator int() { return -1; }
        [[nodiscard]] const char* what() const noexcept override{
            return "Accessed pointer is a null pointer";
        }
    };

    class PNT_API NullCallbackError final : public std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override{
            return "Callback has not been set and as a result is a null function pointer";
        }
    };

    class PNT_API IndexOutOfBoundsError final : public std::exception
    {
    public:
        operator int() { return -1; }
        [[nodiscard]] const char* what() const noexcept override{
            return "Query index is out of bounds, the result cannot be found, check that your is correct and try again.";
        }
    };

    class PNT_API ShaderProgramCreationError final : public std::exception
    {
    public:
        operator int() { return 0; }
        [[nodiscard]] const char* what() const noexcept override{
            return "Shader Program creation failed. Test the GlError to see the full description.";
        }
    };

    class PNT_API OpenGlContextNotCurrentError final : public std::exception
    {
    public:
        operator int() { return -1; }
        [[nodiscard]] const char* what() const noexcept override{
            return "The opengl context has change and s no more the current glfwWindow.";
        }
    };
}