//
// Created by Eniola Olawale on 10/19/2023.
//

#pragma once

#include "purity_core_pch.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "events.h"


namespace purity{
    class PURITY_API PWindow{
    public:
        using EventCallbackFunction = std::function<void(Event&)>;
    private:
        static void setVersion(int major, int minor);
        GLFWwindow* m_glfwWindow;

    public:
        PWindow();
        static void bindWindowBackendAPI(); // Bind GLFW
        static void unbind(); // UnBind
        void createWindow(int width, int height, const char *title = "Purity Window", int gl_major_v = 4, int gl_minor_v = 5);
        

        inline void setWindowsEventCallbacks(EventCallbackFunction& callbackFunction) 
        { 
            m_data.eventCallbackFunction = callbackFunction; 
        }

        void update();

        inline GLFWwindow*& getWindow()
        {
            return m_glfwWindow;
        }

        inline void setVSync(bool allowVSync) {
            if (allowVSync) {
                glfwSwapInterval(1);
            }
            else {
                glfwSwapInterval(0);
            }
            m_data.vsync = allowVSync;
        }

        inline bool isVSynced() const {
            return m_data.vsync;
        }

        void deleteWindow();
        ~PWindow();

    private:
        struct WindowInfo {
            std::string title;
            uint32_t width, height;
            bool vsync;
            EventCallbackFunction eventCallbackFunction;
        };

        WindowInfo m_data;

    };
}
