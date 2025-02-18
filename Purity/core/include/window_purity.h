//
// Created by Eniola Olawale on 10/19/2023.
//

#pragma once

#include "purity_core_pch.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace purity{

    class PURITY_API PWindow{
    private:
        static void setVersion(int major, int minor);
        GLFWwindow* m_glfwWindow;

    public:
        PWindow();
        static void bindWindowBackendAPI(); // Bind GLFW
        static void unbind(); // UnBind
        static void createWindow(const std::unique_ptr<PWindow>& window, int width, int height, const char *title = "Purity Window", int gl_major_v = 4, int gl_minor_v = 5);

        static void setWindowsEventCallbacks();

        void update();

        inline GLFWwindow*& getWindow()
        {
            return m_glfwWindow;
        }

        void deleteWindow();
        bool windowClose();
        ~PWindow();

    };
}
