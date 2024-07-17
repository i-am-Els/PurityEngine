//
// Created by Eniola Olawale on 12/13/2023.
//

#pragma once
#include <string>
#include <memory>
#include "glew.h"

namespace pnt::graphics
{
    enum ShaderType{
        VertexShader = 0, FragmentShader, GeometryShader
    };


    class PShader {
    private:
        [[nodiscard]] static unsigned int compileShader(pnt::graphics::ShaderType type, unsigned int id) ;
        unsigned int shaderProgramID = 0;
        static unsigned int setUpShader(ShaderType type, const std::string& source);

    public:
        PShader();
        ~PShader();
        /// @brief Extract Source code from Shader file.
        /// @param path - The relative path to the shader.
        /// @return A std::string contained in the file.
        /// @note Works with Absolute paths too.
        static std::string extractSourceFromFile(const char* path);

        /// @brief Creates a Program out of the shader sources.
        /// @param vertexSource - The vertex shader source string.
        /// @param fragmentSource - The fragment shader source string.
        /// @return std::unique_ptr Shader program of type PShader
        static std::unique_ptr<PShader> createShaders(const std::string& vertexSource, const std::string& fragmentSource);

        void bindShader() const;
        static void unbindShader();
        [[nodiscard]] unsigned int GetShaderProgramID() const;
        int getUniformLocation(const char* name) const;
        static int s_getUniformLocation(unsigned int programID, const char* name);
    };

}
