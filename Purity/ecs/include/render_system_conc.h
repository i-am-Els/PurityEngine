//
// Created by Eniola Olawale on 6/17/2024.
//

#pragma once
#include "buffer.h"
#include "renderer.h"
#include "render_system.h"
#include "shader.h"


/***
 * As part of thw ECS, the role of this object will be:
 * 1. To understand and filter what objects need to go to the renderer,
 * 2. Figure out the mapping of objects ID to Shaders required for them
 * 3. Does not handle Debug Rendering information or any real rendering.
 * Unlike other systems with semi-real functionalities, it only prepares data for the renderer.
 ***/

namespace purity::ecs{

    class PURITY_API POpenGLRenderSS final : public IRenderSystem{
    public:
        explicit POpenGLRenderSS();
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
        //
        // void setUpShader() override;
        //
        // VertexBuffer* _vbo;
        // ElementBuffer* _ebo;

        // void SetUpBuffers(VertexBuffer* vbo, ElementBuffer* ebo);

        std::weak_ptr<PRenderComponent> AddComponent(std::weak_ptr<PEntity> entity) override;

        void RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<PRenderComponent> component) override;

        // using EDITOR_Render_Callback = std::function<void()>;
        // void setEditorRenderCallback(const EDITOR_Render_Callback& callback)
        // {
        //     editorRenderCallback = callback;
        // }

    private:
        // EDITOR_Render_Callback editorRenderCallback;
        std::vector<std::shared_ptr<PRenderComponent>> renderComponents;


        // static void clearWindow(GLbitfield masks, graphics::Color color);
        // GLFWwindow* _window;
        // std::unique_ptr<PShader> shader;
        // VertexArray* vertexArray;
        //
        // bool switchShader(std::unique_ptr<PShader> shaderProgram);

        // static void SetUniformVec2(int uniformID, Vector2f vec2);
        // static void SetUniformVec3(int uniformID, Vector3f vec3);

        // PURE_NODISCARD bool hasSomethingToRender() const noexcept;
    };
}
