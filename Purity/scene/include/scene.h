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
        ~PScene();
        //explicit PScene(const ecs::PEntityRegistry& registry );
        ecs::PEntityHandle CreateEntity(const std::string& name);
        ecs::PEntityHandle CreateEntityWithUUID(PUUID uuid, const std::string& name);
        void DestroyEntity(PEntityHandle entity);
        void DestroyEntityWithUUID(PUUID uuid);

        static bool HasAnythingToRender();
        static PScene* LoadScene(const PUUID& scene_id);
        static PScene* UnloadScene();
        auto getID() -> PUUID { return m_scene_id; }

    private:
        PUUID m_scene_id;
        ecs::PEntityRegistry m_registry;
    };
} // purity::scene
