//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "uuid.h"
#include "ecs_conc.h"
#include "entity_registry.h"
#include "scene_graph.h"


namespace purity::ecs
{
    class PEntityHandle;
}

namespace purity {
    class PSystemFinder;
}

namespace purity::scene{

/// IMPORTANT!!!! - A Scene is never created without Loading, and none of its contents can be read without first loading it and attaching it to SceneLayer.
    class PURITY_API PScene  {
    public:
        PScene();
        explicit PScene(const PUUID& id);
        ~PScene();

        //explicit PScene(const ecs::PEntityRegistry& registry );
        ecs::PEntityHandle CreateEntity(const std::string& name);
        ecs::PEntityHandle CreateEntityWithUUID(PUUID uuid, const std::string& name);
        void DestroyEntity(ecs::PEntityHandle entity);
        void DestroyEntityWithUUID(PUUID uuid);

        bool hasAnythingToRender();
        static std::unique_ptr<PScene> LoadScene(const std::string& scene_asset_rel_path);
        static std::unique_ptr<PScene> CreateNewScene(const std::string& scene_name);
        void UnloadScene();
        PURE_INLINE PUUID getID() const { return m_scene_id; }
        PURE_INLINE std::string getName() { return m_scene_name; }
        PURE_INLINE void setName(const std::string& name) { m_scene_name = name; }

        PURE_INLINE void setSourceAssetUUID(PUUID& uuid) { m_sourceAsset_id = uuid; }

		PURE_INLINE const PSceneGraph& getSceneGraph() const { return m_sceneGraph; }

    private:
        PURE_INLINE ecs::PECSService& GetECSService() {
            return m_ecsService;
        }
        PUUID m_scene_id;
        PUUID m_sourceAsset_id;
        std::string m_scene_name; // this is mostly the same as the scene file name in assetDB
        ecs::PEntityRegistry m_registry;
        PECSService m_ecsService;
        PSceneGraph m_sceneGraph; 

        friend class PECSService;
        friend class ecs::PEntityRegistry;

        friend PECSService& ecs::PEntityHandle::getECSService();
    };
} // purity::scene



// PSceneGraph responsibilities
        // SetChild(EntityHandle Parent, EntityHandle child)
        // RevokeParentRelationship(Entity
