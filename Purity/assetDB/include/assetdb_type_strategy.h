//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once
#include "assetdb_query_specs.h"
#include "handle_base.h"
#include "core_macros.h"
#include "assets_types.h"
#include "papplication.h"

//using namespace purity::fileIO;

namespace purity::assetDB
{
    template<class AssetTypeRef>
    class PURITY_API AssetOperationStrategy
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<AssetTypeRef> _spec): spec(_spec)
        {
        }
        ~AssetOperationStrategy() = default;
        std::shared_ptr<AssetTypeRef> ReadOperation() { return {}; }
        std::shared_ptr<AssetTypeRef> WriteOperation() { return {}; }
        std::shared_ptr<AssetTypeRef> UpdateOperation() { return {}; }
        std::shared_ptr<AssetTypeRef> DeleteOperation() { return {}; }
        QuerySpec<AssetTypeRef> spec;
    };


    template<>
    class PURITY_API AssetOperationStrategy<PTextureAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PTextureAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PTextureAsset> ReadOperation() { return {}; }
        std::shared_ptr<PTextureAsset> WriteOperation() { return {}; }
        std::shared_ptr<PTextureAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PTextureAsset> DeleteOperation() { return {}; }
        QuerySpec<PTextureAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PSpriteAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PSpriteAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PSpriteAsset> ReadOperation() { return {}; }
        std::shared_ptr<PSpriteAsset> WriteOperation() { return {}; }
        std::shared_ptr<PSpriteAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PSpriteAsset> DeleteOperation() { return {}; }
        QuerySpec<PSpriteAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PShaderAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PShaderAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PShaderAsset> ReadOperation() { return {}; }
        std::shared_ptr<PShaderAsset> WriteOperation() { return {}; }
        std::shared_ptr<PShaderAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PShaderAsset> DeleteOperation() { return {}; }
        QuerySpec<PShaderAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PMeshAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PMeshAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PMeshAsset> ReadOperation() { return {}; }
        std::shared_ptr<PMeshAsset> WriteOperation() { return {}; }
        std::shared_ptr<PMeshAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PMeshAsset> DeleteOperation() { return {}; }
        QuerySpec<PMeshAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PSkeletonAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PSkeletonAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PSkeletonAsset> ReadOperation() { return {}; }
        std::shared_ptr<PSkeletonAsset> WriteOperation() { return {}; }
        std::shared_ptr<PSkeletonAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PSkeletonAsset> DeleteOperation() { return {}; }
        QuerySpec<PSkeletonAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PStaticMeshAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PStaticMeshAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PStaticMeshAsset> ReadOperation() { return {}; }
        std::shared_ptr<PStaticMeshAsset> WriteOperation() { return {}; }
        std::shared_ptr<PStaticMeshAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PStaticMeshAsset> DeleteOperation() { return {}; }
        QuerySpec<PStaticMeshAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PMaterialAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PMaterialAsset>& _spec)
            : spec(_spec)
        {
        }
        ~AssetOperationStrategy() = default;
        std::shared_ptr<PMaterialAsset> ReadOperation() { return {}; }
        std::shared_ptr<PMaterialAsset> WriteOperation() { return {}; }
        std::shared_ptr<PMaterialAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PMaterialAsset> DeleteOperation() { return {}; }
        QuerySpec<PMaterialAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PSplineAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PSplineAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PSplineAsset> ReadOperation() { return {}; }
        std::shared_ptr<PSplineAsset> WriteOperation() { return {}; }
        std::shared_ptr<PSplineAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PSplineAsset> DeleteOperation() { return {}; }
        QuerySpec<PSplineAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PP2DPolygonMeshAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PP2DPolygonMeshAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PP2DPolygonMeshAsset> ReadOperation() { return {}; }
        std::shared_ptr<PP2DPolygonMeshAsset> WriteOperation() { return {}; }
        std::shared_ptr<PP2DPolygonMeshAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PP2DPolygonMeshAsset> DeleteOperation() { return {}; }
        QuerySpec<PP2DPolygonMeshAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PSoundSourceAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PSoundSourceAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PSoundSourceAsset> ReadOperation() { return {}; }
        std::shared_ptr<PSoundSourceAsset> WriteOperation() { return {}; }
        std::shared_ptr<PSoundSourceAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PSoundSourceAsset> DeleteOperation() { return {}; }
        QuerySpec<PSoundSourceAsset> spec;
    };

    template<>
     class PURITY_API AssetOperationStrategy<PP3DSoundSourceAsset>
     {
     public:
         explicit AssetOperationStrategy(const QuerySpec<PP3DSoundSourceAsset>& _spec)
             : spec(_spec)
         {
         }

        ~AssetOperationStrategy() = default;
         std::shared_ptr<PP3DSoundSourceAsset> ReadOperation() { return {}; }
         std::shared_ptr<PP3DSoundSourceAsset> WriteOperation() { return {}; }
         std::shared_ptr<PP3DSoundSourceAsset> UpdateOperation() { return {}; }
         std::shared_ptr<PP3DSoundSourceAsset> DeleteOperation() { return {}; }
         QuerySpec<PP3DSoundSourceAsset> spec;
     };

    template<>
    class PURITY_API AssetOperationStrategy<PLevelAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PLevelAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PLevelAsset> ReadOperation() 
        { 
            std::shared_ptr<PLevelAsset> levelAsset;
            try
            {
                auto levelAsset_obj = ObjectRegistry::findObject(this->spec.assetRecord.uuid);
                if (levelAsset_obj == nullptr) { 
                    throw exceptions::NullPointerError("Asset Pointer is null, you might need to load it into runtime environment... \nLoading...");
                    /// TODO : Assumption is that this fella below will pull the fully serialised data into proper struct.
                    levelAsset = Serializer::load<PLevelAsset>(spec.assetRecord.metaPath.string());
                    //levelAsset->setID(this->spec.assetRecord.uuid);

                }
                levelAsset = dynamic_pointer_cast<PLevelAsset>(levelAsset_obj);
                if (levelAsset == nullptr) {
                    throw exceptions::NullPointerError("Type Mismatch");
                }

            }
            catch (const std::exception& e) {
                PLog::echoMessage(e.what(), LogLevel::Error);
                return nullptr;
            }

            return levelAsset; 
        }

        std::shared_ptr<PLevelAsset> WriteOperation()
        {
            auto scene = PSystemFinder::GetScene();
            if (scene == nullptr) { throw std::runtime_error("Scene is null"); }

            auto levelAsset = assetDB::PLevelAsset::create();
            levelAsset->setID(this->spec.assetRecord.uuid);
            levelAsset->SetScene(scene);

            // Serialize to disk
            Serializer::save(levelAsset, spec.assetRecord.metaPath.string());

            return levelAsset;
        }

        std::shared_ptr<PLevelAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PLevelAsset> DeleteOperation() { return {}; }
        QuerySpec<PLevelAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PParticleAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PParticleAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PParticleAsset> ReadOperation() { return {}; }
        std::shared_ptr<PParticleAsset> WriteOperation() { return {}; }
        std::shared_ptr<PParticleAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PParticleAsset> DeleteOperation() { return {}; }
        QuerySpec<PParticleAsset> spec;
    };

    template<>
    class PURITY_API AssetOperationStrategy<PRenderMapAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PRenderMapAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PRenderMapAsset> ReadOperation() { return {}; }
        std::shared_ptr<PRenderMapAsset> WriteOperation() { return {}; }
        std::shared_ptr<PRenderMapAsset> UpdateOperation() { return {}; }
        std::shared_ptr<PRenderMapAsset> DeleteOperation() { return {}; }
        QuerySpec<PRenderMapAsset> spec;
    };


    template<>
    class PURITY_API AssetOperationStrategy<PProjectAsset>
    {
    public:
        explicit AssetOperationStrategy(const QuerySpec<PProjectAsset>& _spec)
            : spec(_spec)
        {
        }

        ~AssetOperationStrategy() = default;
        std::shared_ptr<PProjectAsset> ReadOperation() { return {}; }
        std::shared_ptr<PProjectAsset> WriteOperation() { return {}; }

        std::shared_ptr<PProjectAsset> UpdateOperation() { 
            // Define the default project JSON structure 

            auto projectAsset = assetDB::PProjectAsset::create();
            projectAsset->setID(this->spec.assetRecord.uuid);

            projectAsset->project_name = spec.assetRecord.name;
            projectAsset->start_up_scene = spec.startup_scene_path;
            projectAsset->projectDB = "Assets/" + spec.assetRecord.name + ".peDB";
            // Serialize to disk
            Serializer::save(projectAsset, spec.assetRecord.metaPath.string());

            return projectAsset;
        }

        std::shared_ptr<PProjectAsset> DeleteOperation() { return {}; }
        QuerySpec<PProjectAsset> spec;
    };
}
