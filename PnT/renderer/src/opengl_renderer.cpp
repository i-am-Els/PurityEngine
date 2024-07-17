//
// Created by Eniola Olawale on 6/17/2024.
//

#include "opengl_renderer.h"
#include "log.h"
#include "data_hash_table.h"

namespace pnt::graphics{

    void POpenGLRenderSS::setUpShader() {
        auto vert = PShader::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_vert"]);
        auto frag = PShader::extractSourceFromFile(pnt::artifacts::hFiles["basic_shader_frag"]);
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
        glUniform2fv(uniformID, 1, static_cast<float*>(vec2));
    }

    void POpenGLRenderSS::SetUniformVec3(int uniformID, Vector3f vec3) {
        glUniform3fv(uniformID, 1, static_cast<float*>(vec3));
    }


    void POpenGLRenderSS::init() {
        shader = std::make_unique<PShader>();
        setUpShader();

        vertexArray->init(); // setup vao, bind and configure it
        // TODO - bind vbo here;
//        // _vbo->bindBuffer();
//        // _ebo->bindBuffer();
//#ifdef HACK_
//        _vbo->bindBuffer();
//        _ebo->bindBuffer();
//#endif //HACK_
//        vertexArray->addAttribute(0, 3, sizeof(float) * 3, nullptr); // add attribute to vao
//        glEnable(GL_DEPTH_TEST);
//        // TODO - unbind vbo here
//        // _vbo->unbindBuffer();
//        // _ebo->unbindBuffer();
//#ifdef HACK_
//        _vbo->unbindBuffer();
//        _ebo->unbindBuffer();
//#endif //HACK_
    }

    void POpenGLRenderSS::start() {
        // TODO - bind vbo here;
        // _vbo->bindBuffer();
        // _ebo->bindBuffer();
#ifdef HACK_
        _vbo->bindBuffer();
        _ebo->bindBuffer();
#endif //HACK_
        vertexArray->addAttribute(0, 3, sizeof(float) * 3, nullptr); // add attribute to vao
        glEnable(GL_DEPTH_TEST);
        // TODO - unbind vbo here
        // _vbo->unbindBuffer();
        // _ebo->unbindBuffer();
#ifdef HACK_
        _vbo->unbindBuffer();
        _ebo->unbindBuffer();
#endif //HACK_
    }

    void POpenGLRenderSS::process() {
//        int uniformID = shader->getUniformLocation("posit");
//        POpenGLRenderSS::SetUniformVec2(uniformID, Vector2f(.5f, 0.0f));
    }

    void POpenGLRenderSS::update(float deltaTime) {

    }

    void POpenGLRenderSS::render() {
        clearWindow(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, Color(.5f, .5f, .2f));

        // TODO - update VBO and EBO here
        // _vbo->updateBuffer();
        // _ebo->updateBuffer();
#ifdef HACK_
        _vbo->updateBuffer();
        _ebo->updateBuffer();
#endif //HACK_
        shader->bindShader();
        vertexArray->bindVAO();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        VertexArray::unbindVAO();
        SwapBuffers();
        PShader::unbindShader();
    }

    void POpenGLRenderSS::destroy() {

    }

    void POpenGLRenderSS::AddRenderable(PRenderComponent &comp) {
        renderComponents.push_back(&comp);
    }

    void POpenGLRenderSS::RemoveRenderable(PRenderComponent &comp) {
        std::remove(renderComponents.begin(), renderComponents.end(), &comp);
    }

    void POpenGLRenderSS::clearWindow(GLbitfield masks, graphics::Color color){
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(masks);
    }

    void POpenGLRenderSS::SwapBuffers() {
        glfwSwapBuffers(_window);
    }

    POpenGLRenderSS::POpenGLRenderSS(GLFWwindow* & window) : _window(window){
        vertexArray = new VertexArray();
    }

    POpenGLRenderSS::~POpenGLRenderSS() {
        delete vertexArray;
    }

}