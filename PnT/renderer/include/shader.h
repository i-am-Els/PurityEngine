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
        static std::string extractSourceFromFile(const char* path);
        static std::unique_ptr<PShader> createShaders(const std::string& vertexSource, const std::string& fragmentSource);
        void bindShader() const;
        static void unbindShader();
        [[nodiscard]] unsigned int GetShaderProgramID() const;
        int getUniformLocation(const char* name) const;
        static int s_getUniformLocation(unsigned int programID, const char* name);
    };

}
