//
// Created by Eniola Olawale on 12/13/2023.
//

#include "shader.h"
#include "log.h"
#include <iostream>
#include <memory>

using namespace pnt::graphics;

PShader::PShader() = default;

PShader::~PShader() {
    PLog::echoMessage("Shader Destroyed");
};

void PShader::createShaders(std::unique_ptr<PShader>& shader, const std::string& vertexSource, const std::string& fragmentSource)
{
    shader = std::make_unique<PShader>();
    auto programID = glCreateProgram();
    unsigned int vs = setUpShader(ShaderType::VertexShader, vertexSource);
    unsigned int fs = setUpShader(ShaderType::FragmentShader, fragmentSource);

    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);
    glValidateProgram(programID);

    int linkStat;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStat);
    if (linkStat != GL_TRUE){
        PLog::echoMessage(LogLevel::Error, "Linking Error");
    }

    int validateStat;
    glGetProgramiv(programID, GL_VALIDATE_STATUS, &validateStat);
    if (validateStat != GL_TRUE){
        PLog::echoMessage(LogLevel::Error, "Validation Error");
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    if (programID){
        shader->shaderProgramID = programID;
        PLog::echoMessage("PShader setup is successful!");
        return;
    }

    shader.reset();
    shader = nullptr;
}

void PShader::bindShader() const {
    glUseProgram(shaderProgramID);
}

void PShader::unbindShader() {
    glUseProgram(0);
}

unsigned int PShader::GetShaderProgramID() const {
    return shaderProgramID;
}

/// @brief Setup a shader
/// @param type - ShaderType enum value, the type of shader.
/// @param source - Shader source string defining shader code.
/// @returns 0 - if error occurs.
/// @returns ID <unsigned integer> - No error occurred.
unsigned int PShader::setUpShader(ShaderType type, const std::string& source)
{
    unsigned int ID = 1;
    switch(type)
    {
        case ShaderType::VertexShader:
            ID = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::FragmentShader:
            ID = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case ShaderType::GeometryShader:
            ID = glCreateShader(GL_GEOMETRY_SHADER);
            break;
        default:
            return 0; // Unimplemented shader type
    }
    const char* sourceData = source.c_str();
    glShaderSource(ID, 1, &sourceData, nullptr);


    if (compileShader(type, ID)) // returns 1 - Success || returns 0 - Failed
    {
        return ID; // succeeded
    }
    return 0; // failed

}

/// @brief Compiles a shader
/// @param type - ShaderType enum value, the type of shader to compile.
/// @param id - Shader ID used to locate shader to compile.
/// @returns 0 - if error occurs.
/// @returns 1 - No error occurred.
unsigned int PShader::compileShader(pnt::graphics::ShaderType type, unsigned int id)
{
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile " << (type == ShaderType::VertexShader ? "Vertex" : "Fragment") << " shader!"
                  << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        free(message);
        return 0;
    }
    return 1;
}

int PShader::getUniformLocation(const char *name) const {
    return glGetUniformLocation(shaderProgramID, name);
}

int PShader::s_getUniformLocation(unsigned int programID, const char *name) {
    return glGetUniformLocation(programID, name);
}



