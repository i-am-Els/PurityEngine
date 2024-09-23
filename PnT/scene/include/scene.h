//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "uuid.h"
#include "entity_registry.h"

namespace pnt{
    class PNT_API PScene{
    public:
        PScene() = default;
        ~PScene() = default;
        PScene(const std::unordered_map<PUUID, PEntity*>& entityMap, const ecs::PEntityRegistry& registry );
        ecs::PEntity* CreateEntity(const std::string& name);
        ecs::PEntity* CreateEntityWithUUID(PUUID uuid, const std::string& name);
        void DestroyEntity(PEntity entity);
        void DestroyEntityWithUUID(PUUID uuid);

        std::unordered_map<PUUID, PEntity*> m_entityMap;
        ecs::PEntityRegistry m_registry;
    };
}
