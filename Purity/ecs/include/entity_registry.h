//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "entity_handle.h"
#include "tags.h"


namespace purity::ecs
{
    class PEntityHandle;
}

using namespace commons;
using namespace purity::artifacts;

namespace purity::ecs{
    class PURITY_API PEntityRegistry{
    public:
        PEntityRegistry() = default;
        ~PEntityRegistry();
        PEntityRegistry(const PEntityRegistry& registry) = delete;
        PEntityRegistry operator=(const PEntityRegistry& registry) = delete; // Copy of a class with a unique ptr member iis not allowed
        PURE_NODISCARD PEntityHandle Create(PUUID uuid);
        PURE_NODISCARD PEntityHandle Create(PUUID uuid, const std::string& name);
        void Destroy(const PUUID& uuid);

        PEntityHandle GetEntity(PUUID id);

        std::vector<PEntityHandle> GetEntitiesWithTag(ETags tag, const std::unordered_set<PEntityHandle>& entitiesToIgnore = {});

        bool entityMapIsEmpty()
        {
            return m_entityMap.empty();
        }

    protected:
        std::unordered_map<PUUID, std::shared_ptr<PEntity>> m_entityMap;
    };
}