//
// Created by Eniola Olawale on 10/19/2023.
//

#include "window_pnt.h"
#include "log.h"

namespace pnt::graphics {

    // PWindow

    PWindow::PWindow() {
        window = nullptr;
        PLog::echoMessage("PWindow Constructed!");
    }

    PWindow::~PWindow() = default;

//    PWindow & PWindow::getInstance() {
//        static PWindow instance;
//        return instance;
//    }

    void PWindow::bindWindowBackendAPI() {
        if(!glfwInit()){
            PLog::echoMessage("GLFW failed to initialized!", LogLevel::Error);
        }else{
            PLog::echoMessage("GLFW Initialized Successfully!");
        }
    }

    std::unique_ptr<PWindow> PWindow::createWindow(int width, int height, const char* title, int gl_major_v, int gl_minor_v) {
        std::unique_ptr<PWindow> window = std::make_unique<PWindow>();

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        setVersion(gl_major_v, gl_minor_v);

        window->window = glfwCreateWindow(
                width,
                height,
                title,
                nullptr,
                nullptr
        );

        if(!window->window){
            PLog::echoMessage("Something Went wrong while creating a Window. That's all we know", LogLevel::Error);
            return nullptr;
        }else{
            PLog::echoMessage("Window creation completed successfully!");
        }

        glfwMakeContextCurrent(window->window);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        PNT_ASSERT_MSG(status, "Failed to initialize GLAD!");

        return std::move(window);
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
        glfwDestroyWindow(window);
        window = nullptr;
        PLog::echoMessage("Window Deleted!");
    }

//    void PWindow::terminate() {
//    }

    bool PWindow::windowClose(){
        if (glfwWindowShouldClose(window)){
            deleteWindow();
            return true;
        }
        return false;
    }


    // Modern opengl things
    // Using shaders and the likes to render instead of the legacy mode

}