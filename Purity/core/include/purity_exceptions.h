//
// Created by Eniola Olawale on 9/14/2024.
//

#pragma once


#include "core_macros.h"


namespace purity::exceptions
{
    class PURITY_API NullBufferError final : public std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override{
            return "Buffer pointer is a null pointer";
        }
    };

    class PURITY_API NullPointerError final : public std::exception
    {
    public:
        operator int() { return -1; }
        [[nodiscard]] const char* what() const noexcept override{
            return "Accessed pointer is a null pointer";
        }
    };

    class PURITY_API NullCallbackError final : public std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override{
            return "Callback has not been set and as a result is a null function pointer";
        }
    };

    class PURITY_API IndexOutOfBoundsError final : public std::exception
    {
    public:
        operator int() { return -1; }
        [[nodiscard]] const char* what() const noexcept override{
            return "Query index is out of bounds, the result cannot be found, check that your is correct and try again.";
        }
    };

    class PURITY_API ShaderProgramCreationError final : public std::exception
    {
    public:
        operator int() { return 0; }
        [[nodiscard]] const char* what() const noexcept override{
            return "Shader Program creation failed. Test the GlError to see the full description.";
        }
    };

    class PURITY_API OpenGlContextNotCurrentError final : public std::exception
    {
    public:
        operator int() { return -1; }
        [[nodiscard]] const char* what() const noexcept override{
            return "The opengl context has change and s no more the current glfwWindow.";
        }
    };

    class PURITY_API FileReadError final : public std::exception
    {
    private:
        std::string _message;
    public:
        explicit FileReadError(const char* path)
            : _message(std::string("There was an error while reading the file '") + path + "'.") {
        }
        operator int() { return -1; }
        [[nodiscard]] const char* what() const noexcept override {
            return _message.c_str();
        }
    };
}