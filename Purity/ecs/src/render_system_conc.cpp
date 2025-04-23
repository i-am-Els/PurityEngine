//
// Created by Eniola Olawale on 6/17/2024.
//

#include "render_system_conc.h"
#include "log.h"
#include "data_hash_table.h"
#include "fileio.h"
#include "entity.h"
#include "scene.h"

using namespace purity::fileIO;

namespace purity::ecs {

    void POpenGLRenderSS::setUpShader() {
        auto vert = PFileIO::extractSourceFromFile(purity::artifacts::hFiles["basic_shader_vert"]);
        auto frag = PFileIO::extractSourceFromFile(purity::artifacts::hFiles["basic_shader_frag"]);

        PShader::createShaders(shader, vert, frag);
        if (shader != nullptr && shader->GetShaderProgramID())
            PLog::echoMessage("PShader Up and Running!");
        else PLog::echoMessage("PShader Set up failed!");

    }

    /// @brief The shader needs to have been built in order for this to work correctly
    /// @param shaderProgram - a std::unique_ptr PShader
    /// @return bool - True or False concerning the success of the switch operation.
    /// @note The initial shader is not tempered with if the new is null
    bool POpenGLRenderSS::switchShader(std::unique_ptr<PShader> shaderProgram) {
        if (shaderProgram == nullptr) return false;
        shader = std::move(shaderProgram);
        shader->bindShader();
        return true;
    }

    void POpenGLRenderSS::SetUniformVec2(int uniformID, Vector2f vec2) {
        glUniform2fv(uniformID, 1, static_cast<float *>(vec2));
    }

    void POpenGLRenderSS::SetUniformVec3(int uniformID, Vector3f vec3) {
        glUniform3fv(uniformID, 1, static_cast<float *>(vec3));
    }


    void POpenGLRenderSS::init() {
        shader = std::make_unique<PShader>();
        setUpShader();
    }

    void POpenGLRenderSS::start() {
        vertexArray->init(); // setup vao, bind and configure it
//        _vbo->bindBuffer();
//        _ebo->bindBuffer();
        vertexArray->addAttribute(0, 3, sizeof(float) * 3, nullptr); // add attribute to vao
        glEnable(GL_DEPTH_TEST);
    }

    void POpenGLRenderSS::process() {
//        int uniformID = shader->getUniformLocation("posit");
//        POpenGLRenderSS::SetUniformVec2(uniformID, Vector2f(.5f, 0.0f));
    }

    void POpenGLRenderSS::update(float deltaTime) {

    }

    void POpenGLRenderSS::render() {
        clearWindow(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, Color(.5f, .5f, .2f));
        shader->bindShader();

        if (glfwGetCurrentContext() != _window) {
            PLog::echoMessage("Context is not current!", LogLevel::Error);
            throw OpenGlContextNotCurrentError();
        }
        else {
            if (hasSomethingToRender()) {
                // PLog::echoMessage("Has Something to Render.");
                // vertexArray->bindVAO();
                // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
                // VertexArray::unbindVAO();
            }
        }

        glfwSwapBuffers(_window);
        PShader::unbindShader();
    }

    void POpenGLRenderSS::destroy() {

    }

    void POpenGLRenderSS::clearWindow(GLbitfield masks, const graphics::Color color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(masks);
    }

    POpenGLRenderSS::POpenGLRenderSS(GLFWwindow* window) : _window(window) {
        vertexArray = new VertexArray();
        renderComponents.reserve(128);
        _vbo = nullptr;
        _ebo = nullptr;
    }

    POpenGLRenderSS::~POpenGLRenderSS() {
        delete vertexArray;
        PLog::echoMessage("Destroying OpenGL Render System.");
    }

    PRenderComponent *POpenGLRenderSS::AddComponent(PEntity *entity) {
        try {
            SRenderProfile profile = {true}; // Set the profile of the render component, through the DTO
            renderComponents.emplace_back(std::make_unique<PRenderComponent>(entity, profile));
            return renderComponents.back().get();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Render Comp Generic Assertion failed");
        }
        return nullptr;
    }

    void POpenGLRenderSS::RemoveComponent(PEntity *entity, PRenderComponent *component) {

    }

    void POpenGLRenderSS::SetUpBuffers(VertexBuffer *vbo, ElementBuffer *ebo) {
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

    bool POpenGLRenderSS::hasSomethingToRender() const noexcept {
        return scene::PScene::HasAnythingToRender(); // TODO - Change this method to check if any object with an `enabled` render component is present in the scene
    }

}
