//
// Created by Eniola Olawale on 9/25/2024.
//

#include "mesh_importer.h"

namespace pnt::fileIO{

    MeshImporter::MeshImporter() {

    }

    bool MeshImporter::ImportFile(const std::string &file) {
        Assimp::Importer importer;

        const aiScene* aiScene = importer.ReadFile(file,
                                                   aiProcess_CalcTangentSpace
                                                   | aiProcess_GenNormals
                                                   | aiProcess_Triangulate
                                                   | aiProcess_JoinIdenticalVertices
                                                   | aiProcess_SortByPType
                                                   | aiProcess_MakeLeftHanded);

        if (nullptr == aiScene){
            return false;
        }

        // SceneProcessing(aiScene);
        return true;
    }

}
