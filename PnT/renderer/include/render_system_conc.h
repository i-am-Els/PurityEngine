//
// Created by Eniola Olawale on 6/17/2024.
//

#pragma once
#include "islemath.h"
#include "shader.h"
#include "renderer.h"
#include "linkedList.h"
#include "color.h"
#include "GLFW/glfw3.h"
#include "vertex_array.h"
#include "render_system.h"
#include "buffer.h"
#include "pnt_exceptions.h"


using namespace isle_engine::math;
using namespace pnt::ecs;
using namespace pnt::exceptions;
using namespace pnt::ds;

namespace pnt::graphics{

    class POpenGLRenderSS final : public IRenderSystem{
    public:
        explicit POpenGLRenderSS(GLFWwindow*& window);
        ~POpenGLRenderSS() override;
        POpenGLRenderSS(POpenGLRenderSS&& renderer) = default;

        void init() override;
        void start() override;
        void process() override;
        void update(float deltaTime) override;
        void render() override;
        void destroy() override;

        void setUpShader() override;
        void SwapBuffers() override;

        VertexBuffer* _vbo;
        ElementBuffer* _ebo;

        inline void SetUpBuffers(VertexBuffer* vbo, ElementBuffer* ebo){
            try{
                if (vbo == nullptr || ebo == nullptr){
                    throw NullBufferError();
                }

                this->_vbo = vbo;
                this->_ebo = ebo;
            }
            catch (std::exception& e){
                PLog::echoMessage(LogLevel::Error, e.what());
            }
        }

        PRenderComponent *AddComponent(PEntity* entity) override;

        PRenderComponent *GetComponent(unsigned int id) override;

        void RemoveComponent(PEntity* entity, PRenderComponent *component) override;

        void RemoveComponentByTag(PEntity* entity, PRenderComponent *component, std::string tag) override;

        void RemoveComponentsByTag(PEntity* entity, std::string tag) override;

        PRenderComponent *FindComponentByTag(PEntity* entity, std::string tag) override;

        std::vector<PRenderComponent *> FindComponentsByTag(PEntity* entity, std::string tag) override;

    private:
        std::vector<std::unique_ptr<PRenderComponent>> renderComponents;


        void clearWindow(GLbitfield masks, graphics::Color color);
        GLFWwindow* _window;
        std::unique_ptr<PShader> shader;
        VertexArray* vertexArray;

        bool switchShader(std::unique_ptr<PShader> shaderProgram);

        static void SetUniformVec2(int uniformID, Vector2f vec2);
        static void SetUniformVec3(int uniformID, Vector3f vec3);

    };
}
