//
// Created by Eniola Olawale on 08/07/2025.
//

#pragma once
#include <purity_core_pch.h>
#include "renderer_service.h"
#include <GLFW/glfw3.h>
#include "buffer.h"
#include "shader.h"
#include "color.h"
#include "vertex_array.h"

/***
 * This is the actual 3D renderer. It can be switched to Vulcan Later but for now remains,
 * an openGL renderer with close relationships with the ECS' rendering System.
***/

using namespace isle_engine::math;
using namespace purity::exceptions;
using namespace purity::fileIO;

namespace purity::graphics
{

    class PURITY_API PRendererService final : public ARendererService
    {
    public:
        PNT_TYPE_INDEX_DEF()
        explicit PRendererService(GLFWwindow* window);
        ~PRendererService() noexcept override;

        void preInit(std::any data) override;
        void init() override;
        void postInit() override;
        void start() override;
        void update(float deltaTime) override;
        void process() override;
        void preRender() override;
        void render() override;
        void postRender() override;
        void destroy() override;
        void exit() override;

        static void SetUniformVec2(int uniformID, Vector2f vec2);
        static void SetUniformVec3(int uniformID, Vector3f vec3);


        void setUpShader();

        VertexBuffer* _vbo;
        ElementBuffer* _ebo;

        void SetUpBuffers(VertexBuffer* vbo, ElementBuffer* ebo);

    private:

        static void clearWindow(GLbitfield masks, graphics::Color color);
        GLFWwindow* _window;
        std::unique_ptr<PShader> shader;
        VertexArray* vertexArray;

        bool switchShader(std::unique_ptr<PShader> shaderProgram);

        PURE_NODISCARD bool hasSomethingToRender() const noexcept;
    };
}
