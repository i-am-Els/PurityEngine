//
// Created by Eniola Olawale on 6/17/2024.
//

#pragma once
#include "islemath.h"
#include "shader.h"
#include "renderer.h"
#include "linkedList.h"
#include "isystems.h"
#include "color.h"
#include "glfw3.h"
#include "vertex_array.h"
#include "render_service.h"
#include "service_base.h"

using namespace isle_engine::math;
using namespace pnt::ecs;
using namespace pnt::ds;

namespace pnt::graphics{

    class POpenGLRenderSS : public PServiceBase<IRenderService>, public ISystem{
    public:
        explicit POpenGLRenderSS(GLFWwindow*& window);
        ~POpenGLRenderSS() override;
//        POpenGLRenderSS(const POpenGLRenderSS& renderer) = delete; // Can't copy because shader here is a unique ptr
        POpenGLRenderSS(POpenGLRenderSS&& renderer) = default;

        void init() override;
        void process() override;
        void update(float deltaTime) override;
        void render() override;
        void destroy() override;

        void setUpShader() override;
        void clearWindow(GLbitfield masks, graphics::Color color);
        void SwapBuffers() override;

    private:
        GLFWwindow* _window;
        std::unique_ptr<PShader> shader;
        std::vector<PRenderComponent*> renderComponents;
        VertexArray* vertexArray;

        bool switchShader(std::unique_ptr<PShader> shaderProgram);
        void AddRenderable(PRenderComponent &comp);
        void RemoveRenderable(PRenderComponent &comp);

        static void SetUniformVec2(int uniformID, Vector2f vec2);
        static void SetUniformVec3(int uniformID, Vector3f vec3);
    };
}
