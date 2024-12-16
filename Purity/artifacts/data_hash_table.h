//
// Created by Eniola Olawale on 5/7/2024.
//

#pragma once

#include <map>
#include <string>

namespace purity::artifacts{
    static std::map<std::string, const char*> hFiles{
        {"basic_shader_vert", "Shaders/basicShader.vert"},
        {"basic_shader_frag", "Shaders/basicShader.frag"},
        {"basic_shader_Inv_vert", "Shaders/basicShaderInv.vert"},
        {"basic_shader_Inv_frag", "Shaders/basicShaderInv.frag"}
    };
}
