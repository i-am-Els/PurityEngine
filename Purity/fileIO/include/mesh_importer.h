//
// Created by Eniola Olawale on 9/25/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "vertex_array.h"
#include "buffer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace isle_engine::math;
using namespace purity::graphics;

namespace purity::fileIO{

    class PURITY_API MeshImporter {
    public:
        MeshImporter();

        bool ImportFile(const std::string& file);

        void SceneProcessing(const aiScene* aiScene);

    };

}



