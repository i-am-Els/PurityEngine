//
// Created by Eniola Olawale on 10/19/2023.
//

#pragma once
#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"
//#include "../../vendors/GLFW/include/glfw3.h"

namespace pnt::graphics{
    class Renderer{
    public:
        static GLFWwindow* window;
        unsigned int VAO, VBO, EBO, shader;

        static void bind(); // Bind
        static void unbind(); // UnBind
        static void createWindow();
        static Renderer* instance;
        static void init(); // Initialize the renderer instance
        static void terminate(); // Terminate the renderer instance
        ~Renderer();
    private:
        Renderer();
    };

}
