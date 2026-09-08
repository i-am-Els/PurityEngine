//
// Created by Eniola Olawale on 5/7/2024.
//

#pragma once

#include <map>
#include <string>

namespace purity::artifacts{
    static std::map<std::string, const char*> hFiles{
        {"basic_shader_vert", "Resources/shaders/basicShader.vert"},
        {"basic_shader_frag", "Resources/shaders/basicShader.frag"},
        {"basic_shader_Inv_vert", "Resources/shaders/basicShaderInv.vert"},
        {"basic_shader_Inv_frag", "Resources/shaders/basicShaderInv.frag"}
    };

    static std::map<std::string, std::string> builtInLayerNames{
        {"scene", "SceneLayer"},
        {"ui", "EditorUI"},
        {"game", "GameLayer"}
    };
}
