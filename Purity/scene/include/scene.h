//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "uuid.h"
#include "entity_registry.h"

namespace purity::scene{
    class PURITY_API PScene{
    public:
        PScene() = default;
        ~PScene();
        explicit PScene(const ecs::PEntityRegistry& registry );
        ecs::PEntityHandle CreateEntity(const std::string& name);
        ecs::PEntityHandle CreateEntityWithUUID(PUUID uuid, const std::string& name);
        void DestroyEntity(PEntityHandle entity);
        void DestroyEntityWithUUID(PUUID uuid);

        static bool HasAnythingToRender();

    private:
        ecs::PEntityRegistry m_registry;
    };
} // purity::scene
