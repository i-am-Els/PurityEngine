//
// Created by Eniola Olawale on 6/17/2024.
//

#pragma once
#include "islemath.h"
#include "shader.h"
#include "renderer.h"
#include "color.h"
#include "GLFW/glfw3.h"
#include "vertex_array.h"
#include "render_system.h"
#include "buffer.h"
#include "purity_exceptions.h"


using namespace isle_engine::math;
using namespace purity::ecs;
using namespace purity::graphics;
using namespace purity::exceptions;

namespace purity::ecs{

    class PURITY_API POpenGLRenderSS final : public IRenderSystem{
    public:
        explicit POpenGLRenderSS(GLFWwindow* window);
        ~POpenGLRenderSS() override;
        POpenGLRenderSS(POpenGLRenderSS&& renderer) = default;

        POpenGLRenderSS(const POpenGLRenderSS& manager) = delete;
        POpenGLRenderSS operator=(const POpenGLRenderSS& manager) = delete;

        void init() override;
        void start() override;
        void process() override;
        void update(float deltaTime) override;
        void render() override;
        void destroy() override;

        void setUpShader() override;

        VertexBuffer* _vbo;
        ElementBuffer* _ebo;

        void SetUpBuffers(VertexBuffer* vbo, ElementBuffer* ebo);

        PRenderComponent *AddComponent(PEntity* entity) override;

        void RemoveComponent(PEntity* entity, PRenderComponent *component) override;

    private:
        std::vector<std::unique_ptr<PRenderComponent>> renderComponents;


        static void clearWindow(GLbitfield masks, graphics::Color color);
        GLFWwindow* _window;
        std::unique_ptr<PShader> shader;
        VertexArray* vertexArray;

        bool switchShader(std::unique_ptr<PShader> shaderProgram);

        static void SetUniformVec2(int uniformID, Vector2f vec2);
        static void SetUniformVec3(int uniformID, Vector3f vec3);

        [[nodiscard]] bool hasSomethingToRender() const noexcept;
    };
}
