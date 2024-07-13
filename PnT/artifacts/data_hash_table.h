//
// Created by Eniola Olawale on 5/7/2024.
//

#pragma once

#include <map>
#include <string>

namespace pnt::artifacts{
    static std::map<std::string, const char*> hFiles{
        {"basic_shader_vert", "PnT/artifacts/shaders/basicShader.vert"},
        {"basic_shader_frag", "PnT/artifacts/shaders/basicShader.frag"},
        {"basic_shader_Inv_vert", "PnT/artifacts/shaders/basicShaderInv.vert"},
        {"basic_shader_Inv_frag", "PnT/artifacts/shaders/basicShaderInv.frag"}
    };
}
