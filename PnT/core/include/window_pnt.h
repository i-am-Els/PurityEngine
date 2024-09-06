//
// Created by Eniola Olawale on 10/19/2023.
//

#pragma once

#include "pnt_core_pch.h"

#include "core_macros.h"
#include "glad/glad.h"
#include "glfw3.h"

//using namespace isle_engine::math;

namespace pnt::graphics{

    class PWindow{
    private:
        static void setVersion(int major, int minor);
        GLFWwindow* window;

    public:
        PWindow();
        static void bindWindowBackendAPI(); // Bind GLFW
        static void unbind(); // UnBind
        static std::unique_ptr<PWindow> createWindow(int width, int height, const char *title = "PnT Window", int gl_major_v = 4, int gl_minor_v = 0);

        inline GLFWwindow*& getWindow()
        {
            return window;
        }

        void deleteWindow();
        bool windowClose();
        ~PWindow();

    };
}
