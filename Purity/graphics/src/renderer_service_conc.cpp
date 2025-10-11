//
// Created by Eniola Olawale on 08/07/2025.
//

#include "renderer_service_conc.h"
#include "papplication.h"
#include "data_hash_table.h"
#include "fileio.h"


namespace purity::graphics
{
    PRendererService::PRendererService(GLFWwindow* window) : _window(window) {
        vertexArray = new VertexArray();
        _vbo = nullptr;
        _ebo = nullptr;
    }

    PRendererService::~PRendererService() noexcept
    {
        delete vertexArray;
        PLog::echoMessage("Destroying 3D Renderer.");
        PRendererService::exit();
    }

    void PRendererService::preInit(std::any data)
    {
    }

    void PRendererService::init()
    {
        shader = std::make_unique<PShader>();
        setUpShader();
    }

    void PRendererService::postInit()
    {
    }

    void PRendererService::start()
    {
        vertexArray->init(); // setup vao, bind and configure it
        //        _vbo->bindBuffer();
        //        _ebo->bindBuffer();
        vertexArray->addAttribute(0, 3, sizeof(float) * 3, nullptr); // add attribute to vao
        glEnable(GL_DEPTH_TEST);
    }

    void PRendererService::update(float deltaTime)
    {
    }

    void PRendererService::process()
    {
    }

    void PRendererService::preRender()
    {
        const auto clearColor = PSystemFinder::GetApplication()->m_projectEditorInfo.clearColor;

        clearWindow(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, clearColor);
        shader->bindShader();
    }

    void PRendererService::render()
    {
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

    void PRendererService::postRender()
    {
    }

    void PRendererService::destroy()
    {
    }

    void PRendererService::exit()
    {
    }
    

    void PRendererService::SetUniformVec2(int uniformID, Vector2f vec2) {
        glUniform2fv(uniformID, 1, static_cast<float *>(vec2));
    }

    void PRendererService::SetUniformVec3(int uniformID, Vector3f vec3) {
        glUniform3fv(uniformID, 1, static_cast<float *>(vec3));
    }

    void PRendererService::clearWindow(GLbitfield masks, const graphics::Color color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(masks);
    }
    
    void PRendererService::setUpShader() {
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
    bool PRendererService::switchShader(std::unique_ptr<PShader> shaderProgram) {
        if (shaderProgram == nullptr) return false;
        shader = std::move(shaderProgram);
        shader->bindShader();
        return true;
    }

    void PRendererService::SetUpBuffers(VertexBuffer *vbo, ElementBuffer *ebo) {
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

    bool PRendererService::hasSomethingToRender() const noexcept
    {
        return scene::PScene::HasAnythingToRender(); // TODO - Change this method to check if any object with an `enabled` render component is present in the scene
    }
}
