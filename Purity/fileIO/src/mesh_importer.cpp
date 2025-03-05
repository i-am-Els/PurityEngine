//
// Created by Eniola Olawale on 9/25/2024.
//

#include "mesh_importer.h"
#include "log.h"

namespace purity::fileIO{

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
            PLog::echoMessage(purity::LogLevel::Error, "%s %s", "Mesh Importer initialization failed", importer.GetErrorString());
            return false;
        }

        SceneProcessing(aiScene);
        return true;
    }

    void MeshImporter::SceneProcessing(const aiScene* aiScene)
    {
    }

}
