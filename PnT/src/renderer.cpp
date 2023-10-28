//
// Created by Eniola Olawale on 10/19/2023.
//

#include "renderer/renderer.h"
#include "log.h"

namespace pnt::graphics {
    Renderer *Renderer::instance = nullptr;
    GLFWwindow* Renderer::window = nullptr;

    Renderer::Renderer() {

    }

    Renderer::~Renderer() = default;

    void Renderer::init() {
        if (instance == nullptr){
            instance = new Renderer();
            Log::echoMessage("Successfully Initialized Graphics::Renderer!", LogLevel::Info);
        }
    }

    void Renderer::terminate() {
        delete instance;
        instance = nullptr;
    }

    void Renderer::bind() {
        if(!glfwInit()){
            Log::echoMessage("GLFW failed to initialized!", LogLevel::Error);
        }else{
            Log::echoMessage("GLFW Initialized Successfully!");
        }

        window = glfwCreateWindow(
                500,
                500,
                "PnT Renderer",
                nullptr,
                nullptr
        );

        if(!window){
            Log::echoMessage("Something Went wrong while creating a Window. That's all we know", LogLevel::Error);
            unbind();
        }else{
            Log::echoMessage("Window creation completed successfully!");
        }
        glfwMakeContextCurrent(window);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        if(glewInit() != GLEW_OK){
            Log::echoMessage("GLEW failed to initialized!", LogLevel::Error);
        }else{
            Log::echoMessage("GLEW Initialized Successfully!");
        }

        while(!glfwWindowShouldClose(window)){
            glfwPollEvents();

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glfwSwapBuffers(window);
        }

        glfwTerminate();
    }

    void Renderer::unbind() {
        glfwTerminate();
    }

    void Renderer::createWindow() {

    }
}