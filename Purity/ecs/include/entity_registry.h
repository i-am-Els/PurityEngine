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
    class PECSService;
}

namespace purity::scene {
    class PScene;
}

using namespace commons;
using namespace purity::artifacts;

namespace purity::ecs{
    class PURITY_API PEntityRegistry{
    public:
        explicit PEntityRegistry(scene::PScene* owner) : m_ownerScene(owner){}
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

		//void SetOwningScene(scene::PScene* owner) { m_ownerScene = owner; }
		PURE_INLINE scene::PScene* GetOwningScene() const { return m_ownerScene; }

        PURE_NODISCARD PECSService& GetECSService() const;
    protected:
        PEntityIndex createIndex(); 
        void removeIndex(PEntityIndex index);
        std::unordered_map<PUUID, std::shared_ptr<PEntity>> m_entityMap;

        std::queue<PEntityIndex> m_freeIndices;
        static inline uint32_t s_indexCounter = 1;
        scene::PScene* m_ownerScene;
    };
}
