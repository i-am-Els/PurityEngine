//
// Created by Eniola Olawale on 6/17/2024.
//

#include "render_system_conc.h"
#include "log.h"
#include "data_hash_table.h"
#include "fileio.h"
#include "entity.h"

using namespace pnt::fileIO;

namespace pnt::ecs {

    void POpenGLRenderSS::setUpShader() {
        auto vert = PFileIO::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_vert"]);
        auto frag = PFileIO::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_frag"]);
        shader = PShader::createShaders(vert, frag);
        if (shader->GetShaderProgramID())
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
        _vbo->bindBuffer();
        _ebo->bindBuffer();

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
        vertexArray->bindVAO();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        VertexArray::unbindVAO();
        SwapBuffers();
        PShader::unbindShader();
    }

    void POpenGLRenderSS::destroy() {

    }

    void POpenGLRenderSS::clearWindow(GLbitfield masks, graphics::Color color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(masks);
    }

    void POpenGLRenderSS::SwapBuffers() {
        glfwSwapBuffers(_window);
    }

    POpenGLRenderSS::POpenGLRenderSS(GLFWwindow *&window) : _window(window) {
        vertexArray = new VertexArray();
        renderComponents.reserve(100);
    }

    POpenGLRenderSS::~POpenGLRenderSS() {
        delete vertexArray;
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

}
