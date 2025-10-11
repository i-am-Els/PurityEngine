//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "uuid.h"
#include "entity_registry.h"

namespace purity::scene{
    class PURITY_API PScene{
    public:
        PScene();
        explicit PScene(const PUUID& id);
        ~PScene();
        //explicit PScene(const ecs::PEntityRegistry& registry );
        ecs::PEntityHandle CreateEntity(const std::string& name);
        ecs::PEntityHandle CreateEntityWithUUID(PUUID uuid, const std::string& name);
        void DestroyEntity(PEntityHandle entity);
        void DestroyEntityWithUUID(PUUID uuid);

        bool hasAnythingToRender();
        static std::unique_ptr<PScene> LoadScene(const PUUID& scene_id);
        void UnloadScene();
        auto getID() -> PUUID { return m_scene_id; }

    private:
        PUUID m_scene_id;
        std::string m_scene_name; // this is mostly the same as the scene file name in assetDB
        ecs::PEntityRegistry m_registry;
    };
} // purity::scene
