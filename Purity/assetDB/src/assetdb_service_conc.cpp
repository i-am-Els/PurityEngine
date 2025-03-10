//
// Created by Eniola Olawale on 9/13/2024.
//

#include "assetdb_service_conc.h"

#include "papplication.h"

namespace purity::assetDB{
    void PAssetDatabase::preInit(std::any data)
    {
        if(!data.has_value())
        {
            throw std::runtime_error("std::any passed without any value!!!");
        }
        if(const auto* map_ptr = std::any_cast<std::map<PUUID, std::string>>(&data))
        {
            if(!map_ptr->empty())
            {
                for (const auto& [id, path] : *map_ptr)
                {
                    m_AssetContainer[id] = {id, path};
                    std::cout << "Inside assetDB we add id: " << id << " to asset database metadata container" << std::endl;
                }
            }
        }else
        {
            throw std::runtime_error("Incorrect type in std::any. Expected std::map<PUUID, std::string>.");
        }
    }

    void PAssetDatabase::postInit()
    {
    }

    void PAssetDatabase::init() {
        // queryDBForAsset({QueryStaticMeshAssetSpec("gun", "gun.fbx", "material.ml"), QueryOperation::Read});

    }

    void PAssetDatabase::destroy() {

    }

    void PAssetDatabase::exit()
    {
    }
}
