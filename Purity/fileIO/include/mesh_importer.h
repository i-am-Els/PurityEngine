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

#include "importer.h"

using namespace isle_engine::math;
using namespace purity::graphics;

namespace purity::fileIO{

    class PURITY_API MeshImporter final : public PImporter {
    public:
        MeshImporter() = default;
        bool importFile(const std::string& filePath) override;

        void SceneProcessing(const aiScene* aiScene);
        ~MeshImporter() override;
    };

}



