//
// Created by Eniola Olawale on 9/13/2024.
//

#include "assetdb_service_conc.h"

#include "papplication.h"

namespace purity::assetDB{
    void PAssetDatabase::preInit(std::any& data)
    {
        m_Database.create_or_open_db(PSystemFinder::GetApplication()->get_DB_file_path());

        if(!data.has_value())
        {
            throw std::runtime_error("std::any passed without any value!!!");
        }
        if(const auto* map_ptr = std::any_cast<std::map<PUUID, AssetRecord>>(&data))
        {
            if(!map_ptr->empty())
            {
                m_AssetContainer = std::move(*map_ptr);

                data.reset();
            }
        }else
        {
            throw std::runtime_error("Incorrect type in std::any. Expected std::map<PUUID, AssetRecord>.");
        }
    }

    void PAssetDatabase::postInit()
    {
    }

    void PAssetDatabase::init() {
        // Fill Content Drawer with data if available yet. (GUI must be in place for this)...
        for(const auto& [id, record] : m_AssetContainer)
        {

        }
        // queryDBForAsset({QueryStaticMeshAssetSpec("gun", "gun.fbx", "material.ml"), QueryOperation::Read});

    }

    void PAssetDatabase::destroy() {
        m_Database.close_db();
    }

    void PAssetDatabase::exit()
    {
    }


}
