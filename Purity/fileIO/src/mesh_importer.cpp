//
// Created by Eniola Olawale on 9/25/2024.
//

#include "mesh_importer.h"
#include "log.h"

namespace purity::fileIO{


    bool MeshImporter::importFile(const std::string &filePath) {
        Assimp::Importer importer;

        const aiScene* aiScene = importer.ReadFile(filePath,
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

    MeshImporter::~MeshImporter()
    {
        PLog::echoMessage("Destroying Mesh Importer");
    }

}
