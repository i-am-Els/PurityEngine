//
// Created by Eniola Olawale on 10/19/2023.
//

#include "window_pnt.h"
#include "log.h"

namespace pnt {

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

    void PWindow::createWindow(const std::unique_ptr<PWindow>& window, int width, int height, const char* title, int gl_major_v, int gl_minor_v) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        setVersion(gl_major_v, gl_minor_v);

        window->m_glfwWindow = glfwCreateWindow(
                width,
                height,
                title,
                nullptr,
                nullptr
        );

        if(!window->m_glfwWindow){
            PLog::echoMessage("Something Went wrong while creating a Window. That's all we know", LogLevel::Error);
            return;
        }else{
            PLog::echoMessage("Window creation completed successfully!");
        }

        glfwMakeContextCurrent(window->m_glfwWindow);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        PNT_ASSERT_MSG(status, "Failed to initialize GLAD!");
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

//    void PWindow::terminate() {
//    }

    bool PWindow::windowClose(){
        if (glfwWindowShouldClose(m_glfwWindow)){
            deleteWindow();
            return true;
        }
        return false;
    }

    void PWindow::update() {

    }


    // Modern opengl things
    // Using shaders and the likes to render instead of the legacy mode

}