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
#include "render_system.h"
#include "service_base.h"


#ifdef HACK_
#include "buffer.h"
#include "mesh.h"
#endif //HACK_

using namespace isle_engine::math;
using namespace pnt::ecs;
using namespace pnt::ds;

namespace pnt::graphics{

    class POpenGLRenderSS : public IRenderSystem{
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

        inline void SetHackMeshBuffers(VertexBuffer* vbo, ElementBuffer* ebo){
            try{
                if (vbo == nullptr || ebo == nullptr){
                    throw -1;
                }

                this->_vbo = vbo;
                this->_ebo = ebo;
            }
            catch (int e){
                PLog::echoMessage(LogLevel::Error, "Null Incoming Buffers");
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
