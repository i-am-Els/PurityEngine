//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "entity_handle.h"


using namespace commons;

namespace purity::ecs{
    class PURITY_API PEntityRegistry{
    public:
        PEntityRegistry() = default;
        ~PEntityRegistry();
        PEntityRegistry(const PEntityRegistry& registry) = delete;
        PEntityRegistry operator=(const PEntityRegistry& registry) = delete; // Copy of a class with a unique ptr member iis not allowed
        [[nodiscard]]PEntityHandle Create(PUUID uuid);
        [[nodiscard]]PEntityHandle Create(PUUID uuid, const std::string& name);
        void Destroy(PUUID uuid);

        PEntityHandle GetEntity(PUUID id);

        std::vector<PEntityHandle> GetEntitiesWithTag(ETags tag, const std::unordered_set<PEntityHandle>& entitiesToIgnore = {});

        bool entityMapIsEmpty()
        {
            return m_entityMap.empty();
        }

    protected:
        std::unordered_map<PUUID, std::unique_ptr<PEntity>> m_entityMap;
    };
}