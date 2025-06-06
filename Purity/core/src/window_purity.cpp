//
// Created by Eniola Olawale on 10/19/2023.
//

#include "window_purity.h"
#include "log.h"
#include <window_events.h>
#include <keyboard_events.h>
#include <mouse_events.h>

namespace purity {

    // PWindow

    PWindow::PWindow() {
        m_glfwWindow = nullptr;
        PLog::echoMessage("PWindow Constructed!");
    }

    PWindow::~PWindow() {
        PLog::echoMessage("Destroying Window.");
    }

    void PWindow::bindWindowBackendAPI() {
        if(!glfwInit()){
            PLog::echoMessage("GLFW failed to initialized!", LogLevel::Error);
        }else{
            PLog::echoMessage("GLFW Initialized Successfully!");
        }
    }

    void PWindow::createWindow(int width, int height, const char* title, int gl_major_v, int gl_minor_v) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        setVersion(gl_major_v, gl_minor_v);

        m_data.width = width;
        m_data.height = height;
        m_data.title = title;

        m_glfwWindow = glfwCreateWindow(
                width,
                height,
                title,
                nullptr,
                nullptr
        );

        if(!m_glfwWindow){
            PLog::echoMessage("Something Went wrong while creating a Window. That's all we know", LogLevel::Error);
            return;
        }else{
            PLog::echoMessage("Window creation completed successfully!");
        }

        glfwMakeContextCurrent(m_glfwWindow);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        PURITY_ASSERT_MSG(status, "Failed to initialize GLAD!");

        glfwSetWindowUserPointer(m_glfwWindow, &m_data);
        setVSync(true);

        glfwSetCharCallback(m_glfwWindow, [](GLFWwindow* window, unsigned int codepoint)
        {
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(codepoint);
            info.eventCallbackFunction(event);
        });

        glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, int width, int height){
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);
            info.width = width;
            info.height = height;

            WindowResizeEvent event(width, height);
            info.eventCallbackFunction(event);
        });

        glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow* window){
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            info.eventCallbackFunction(event);
        });

        glfwSetCursorEnterCallback(m_glfwWindow, [](GLFWwindow* window, int entered)
        {
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);

            WindowCursorEnterEvent event(entered);
            info.eventCallbackFunction(event);
        });

        glfwSetWindowFocusCallback(m_glfwWindow, [](GLFWwindow* window, int focused){
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);

            WindowFocusEvent event(focused);
            info.eventCallbackFunction(event);
        });

        glfwSetWindowPosCallback(m_glfwWindow, [](GLFWwindow* window, int xpos, int ypos)
        {
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);

            WindowMovedEvent event(xpos, ypos);
            info.eventCallbackFunction(event);
        });

        glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, int key, int scanCode, int action, int mods){
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);
            // USE ISLE KEYCODE

            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    info.eventCallbackFunction(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    info.eventCallbackFunction(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    info.eventCallbackFunction(event);
                    break;
                }
                default:
                {
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, int button, int action, int mods){
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    info.eventCallbackFunction(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    info.eventCallbackFunction(event);
                    break;
                }
                default:
                {
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            info.eventCallbackFunction(event);
        });

        glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double xPos, double yPos){
            WindowInfo& info =  *(WindowInfo*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            info.eventCallbackFunction(event);
        });
    }

    void PWindow::setVersion(int major, int minor) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    }

    void PWindow::unbind() {
        glfwTerminate();
        PLog::echoMessage("PWindow unbound!");
    }

    void PWindow::deleteWindow() {
        glfwDestroyWindow(m_glfwWindow);
        m_glfwWindow = nullptr;
        PLog::echoMessage("Window Deleted!");
    }

    /*void PWindow::terminate() {
    }*/


    void PWindow::update() {

    }

}